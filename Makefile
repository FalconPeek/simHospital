# =========================
# make → compila y te muestra el menú de acciones.
# =========================
# make run → ejecuta build/myprogram.
# =========================
# make term / make termm FILE=mod → abre nuevas terminales (separás salidas por binario).
# =========================
# make DEBUG=1 → build de depuración (símbolos + sanitizers en Linux).
# =========================


# =========================
# Toolchain y flags
# =========================
CC      = gcc
CFLAGS  = -std=c17 -Wall -Wextra -Wpedantic -O2 -I./dat -I./archivos
LIBS    =

# DEBUG=1 -> símbolos + sanitizers (en Linux)
DEBUG ?= 0
ifeq ($(DEBUG),1)
  CFLAGS += -O0 -g -fno-omit-frame-pointer
  ifneq ($(OS),Windows_NT)
    CFLAGS += -fsanitize=address,undefined
    LIBS   += -fsanitize=address,undefined
  endif
endif

# =========================
# Carpetas / SO
# =========================
BINDIR  = build
OBJDIR  = build
LOGDIR  = build/logs

ifeq ($(OS),Windows_NT)
  EXEEXT := .exe
else
  EXEEXT :=
endif

# =========================
# Fuentes
# =========================
SRCS_ALL := $(wildcard *.c)
APP_MAIN := main.c

# (Opcional) módulos con su propio main para pruebas, sin ".c"
# Ejemplo: MODULES_WITH_MAIN := audio_test play_demo
MODULES_WITH_MAIN :=

# Excluir los módulos con main del set de "librería"
LIB_EXCLUDE := $(APP_MAIN) $(addsuffix .c,$(MODULES_WITH_MAIN))
LIB_SRCS    := $(filter-out $(LIB_EXCLUDE),$(SRCS_ALL))

# Derivados
TARGET       := myprogram
TARGET_PATH  := $(BINDIR)/$(TARGET)$(EXEEXT)
OBJS         := $(LIB_SRCS:%.c=$(OBJDIR)/%.o)
MODULE_BINS  := $(addprefix $(BINDIR)/,$(addsuffix $(EXEEXT),$(MODULES_WITH_MAIN)))

.PHONY: all post_build print-help run runm term termm dbg dbgm clean mrproper

# =========================
# Build
# =========================
all: $(TARGET_PATH) $(MODULE_BINS) post_build

post_build:
	@$(MAKE) --no-print-directory print-help

print-help:
	@echo "------------------------------------------------------------"
	@echo "Build OK -> Siguientes pasos:"
	@echo "  make run              # Ejecutar app principal"
	@echo "  make term             # Abrir app en nueva terminal"
	@echo "  make dbg              # Depurar app principal con gdb"
	@echo "  make runm FILE=mod    # Ejecutar modulo (sin .c) con main propio"
	@echo "  make termm FILE=mod   # Abrir modulo en nueva terminal"
	@echo "  make dbgm FILE=mod    # Depurar modulo con gdb"
	@echo "  make clean            # Limpiar objetos/ejecutables en build/"
	@echo "  make mrproper         # Borrar carpeta build/"
	@echo "  make DEBUG=1          # Compilar con simbolos y sanitizers (Linux)"
	@echo "Logs de compilacion: $(LOGDIR)/<archivo>.log"
	@echo "------------------------------------------------------------"

# App principal: main.c + objetos de librería
$(TARGET_PATH): $(APP_MAIN) $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Binarios de prueba por modulo con main propio
$(BINDIR)/%$(EXEEXT): %.c $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Objetos de librería (con logs por archivo)
$(OBJDIR)/%.o: %.c | $(OBJDIR) $(LOGDIR)
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c $< -o $@ > $(LOGDIR)/$*.log 2>&1 \
	 || (echo "✖ Error en $< (ver $(LOGDIR)/$*.log)"; tail -n 25 $(LOGDIR)/$*.log; exit 1)

# Crear carpetas
$(BINDIR) $(OBJDIR) $(LOGDIR):
	@mkdir -p $@

# =========================
# Run
# =========================
run: $(TARGET_PATH)
	./$(TARGET_PATH)

runm: $(BINDIR)/$(FILE)$(EXEEXT)
	./$<

# Nueva terminal para principal
term: $(TARGET_PATH)
ifeq ($(OS),Windows_NT)
	@cmd.exe /c start "" cmd /k "$(TARGET_PATH)"
else
	@if command -v gnome-terminal >/dev/null 2>&1; then \
		gnome-terminal -- bash -lc '$(TARGET_PATH); echo; read -n1 -p "ENTER para cerrar..."'; \
	elif command -v xterm >/dev/null 2>&1; then \
		xterm -hold -e $(TARGET_PATH); \
	else \
		$(TARGET_PATH); \
	fi
endif

# Nueva terminal para modulo: make termm FILE=mod
termm: $(BINDIR)/$(FILE)$(EXEEXT)
ifeq ($(OS),Windows_NT)
	@cmd.exe /c start "" cmd /k "$<"
else
	@if command -v gnome-terminal >/dev/null 2>&1; then \
		gnome-terminal -- bash -lc '$<; echo; read -n1 -p "ENTER para cerrar..."'; \
	elif command -v xterm >/dev/null 2>&1; then \
		xterm -hold -e $<; \
	else \
		$<; \
	fi
endif

# =========================
# Debug
# =========================
dbg: $(TARGET_PATH)
ifeq ($(OS),Windows_NT)
	@cmd.exe /c start "" cmd /k "gdb -q $(TARGET_PATH)"
else
	@if command -v gnome-terminal >/dev/null 2>&1; then \
		gnome-terminal -- bash -lc 'gdb -q $(TARGET_PATH)'; \
	elif command -v xterm >/dev/null 2>&1; then \
		xterm -e gdb -q $(TARGET_PATH); \
	else \
		gdb -q $(TARGET_PATH); \
	fi
endif

dbgm: $(BINDIR)/$(FILE)$(EXEEXT)
ifeq ($(OS),Windows_NT)
	@cmd.exe /c start "" cmd /k "gdb -q $<"
else
	@if command -v gnome-terminal >/dev/null 2>&1; then \
		gnome-terminal -- bash -lc 'gdb -q $<'; \
	elif command -v xterm >/dev/null 2>&1; then \
		xterm -e gdb -q $<; \
	else \
		gdb -q $<; \
	fi
endif

# =========================
# Limpieza
# =========================
clean:
	@rm -f $(OBJDIR)/*.o $(TARGET_PATH) $(MODULE_BINS) $(BINDIR)/*.exe $(BINDIR)/*.out $(BINDIR)/*.bin

mrproper: clean
	@rm -rf $(BINDIR)
