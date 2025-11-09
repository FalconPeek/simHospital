![Build](https://img.shields.io/badge/build-make-brightgreen)(#)
![Lang](https://img.shields.io/badge/C-std%3Ac99-blue)(#)
![OS](https://img.shields.io/badge/OS-Linux%20%7C%20WSL%20%7C%20macOS-lightgrey)(#)
![License](https://img.shields.io/badge/license-MIT-informational)(#)
![Status](https://img.shields.io/badge/status-en%20desarrollo-yellow)(#)

> **Objetivo:** simular la atención de pacientes con **prioridades** y **especialidades**, usando **colas de prioridad**, **listas enlazadas**, **pilas**, **archivos binarios**, **ordenamientos** y **búsqueda binaria**. Proyecto pensado para **Algoritmos y Estructuras de Datos II** (C estándar, TADs).

---

## 📚 Tabla de contenidos
- [Arquitectura y TADs](#-arquitectura-y-tads)
- [Estructura del proyecto](#-estructura-del-proyecto)
- [Requisitos](#-requisitos)
- [Primer inicio (clonar y compilar)](#-primer-inicio-clonar-y-compilar)
- [Uso rápido](#-uso-rápido)
- [Makefile (targets)](#-makefile-targets)
- [Flujo de trabajo con Git](#-flujo-de-trabajo-con-git)
- [Convenciones del equipo](#-convenciones-del-equipo)
- [Diagrama de flujo (resumen)](#-diagrama-de-flujo-resumen)
- [Roadmap](#-roadmap)
- [Pruebas](#-pruebas)
- [Troubleshooting](#-troubleshooting)
- [Créditos y roles](#-créditos-y-roles)
- [Licencia](#-licencia)

---

## 🧱 Arquitectura y TADs
- **Cola de prioridad (multicola FIFO)** → pacientes esperando (por `tPrioridad` P1..P5).
- **Lista enlazada** de **médicxs** por `tEspecialidad`; búsqueda de disponible.
- **Pila** → historial inmediato de atenciones.
- **Archivos binarios** (`atenciones.bin`) → auditoría y reportes.
- **Ordenamientos** (métodos directos) → por espera, edad, etc.
- **Búsqueda binaria** → por DNI/código.
- **Corte de control** → estadísticas por especialidad.

TADs expuestos en `include/`:
cabeza.h - 