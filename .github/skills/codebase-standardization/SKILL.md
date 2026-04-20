---
name: codebase-standardization
description: 'Padroniza nomes de diretorios e documentacao, corrige links quebrados e atualiza README raiz conforme a estrutura real do codebase. Use para: padronizacao de pastas, normalizacao de README.md, sincronizacao do indice de modulos, auditoria de links e referencias antigas.'
argument-hint: 'Convencao alvo + escopo (ex.: kebab-case completo + atualizar README raiz)'
user-invocable: true
---

# Codebase Standardization (Directories, Docs, README Sync)

## Outcome
This skill applies a repeatable workflow to:
- standardize directory names and naming style
- normalize documentation file names and structure
- synchronize root README links with the real repository tree
- prevent stale links and drift after refactors

## When To Use
Use this skill when you need one of these outcomes:
- "padronizar nomes de diretorios"
- "normalizar documentacao"
- "atualizar README com o codebase"
- "corrigir links quebrados no README"
- "alinhar estrutura de pastas e indice"

## Input Required
Collect these inputs before changing files:
1. Target naming convention:
- Option A: `lower-kebab-case` (recommended for cross-platform consistency)
- Option B: keep current top-level names and only normalize docs/links

2. Scope of renames:
- Option A: full repo
- Option B: only top-level folders
- Option C: no folder renames, docs/readme sync only

3. README policy:
- Option A: regenerate index table from filesystem
- Option B: keep curated table and only fix invalid links

## Workflow

### 1. Create Structure Snapshot
Generate objective inventory of current state:
- all top-level directories
- all README-like files (`README.md`, `Readme.md`, `README.MD`)
- naming style distribution
- root README links and their resolution status

Use these checks:
- `Get-ChildItem -Recurse -Directory`
- `Get-ChildItem -Recurse -File | Where-Object { $_.Name -imatch '^readme(\\..+)?$' }`
- parse root README markdown links and test each local path

### 2. Detect Inconsistencies
Identify and classify issues:
- missing target paths from README links
- case mismatches between link and actual folder path
- duplicate naming concepts (example: singular/plural or legacy aliases)
- mixed naming conventions in same level
- non-standard README filenames (`Readme.md`, `README.MD`)

### 3. Decide Migration Strategy
Branch by impact:

If there are many external references or high break risk:
- prefer docs-first strategy
- keep directory names for now
- fix README links to real paths

If you can perform structural refactor safely:
- create rename map and migrate folders with `git mv`
- update references in docs/source
- regenerate README index from live filesystem

If rename is case-only on Windows:
- use two-step rename to avoid case-insensitive collisions
- pattern: `git mv Path TempName` then `git mv TempName path`

If target name collides with an existing path:
- do not auto-rename
- choose a non-conflicting canonical name and confirm with user

### 4. Apply Renames Safely
Rules:
- always use `git mv` (preserve history)
- rename one logical group at a time
- after each batch, run quick link/reference checks

For docs files:
- normalize all README variants to exactly `README.md`
- ensure each documented module has one entry-point README

### 5. Update Documentation Links
Update links in:
- root README
- module README files
- docs indexes and navigation sections

Link policy:
- use repository-relative links
- match exact path casing to avoid cross-platform breakage
- remove or replace legacy links pointing to removed modules

### 6. Synchronize Root README With Real Codebase
For README index table:
- include only modules that currently exist
- map labels to real module paths
- keep numbering contiguous
- keep descriptions aligned with current module responsibility

Recommended generation strategy:
1. list current top-level directories
2. merge with curated title/description metadata
3. output canonical table rows
4. replace stale rows

### 7. Validate Completion
Completion checks (all must pass):
1. no missing local links in root README
2. no case-mismatch links in root README
3. all README filenames are exactly `README.md`
4. no stale references to removed/renamed paths (`rg` search)
5. root README index matches actual repository modules

## Quality Gates
A standardization run is complete only when:
- path naming policy is consistently applied in selected scope
- documentation paths resolve on case-sensitive environments
- no table entry points to non-existing directories
- renamed paths have updated references everywhere relevant

## Repository Baseline Observed (C-Codebase)
This repository currently shows:
- mixed top-level naming styles (`PascalCase`, `lower`, `kebab-case`)
- root README table containing many legacy module links that are no longer top-level directories
- case mismatch examples in links (example: `Memory/` vs real `memory/`)
- README filename variants that should be normalized:
  - `memory/memory-pool/Readme.md`
  - `memory/pointers/function-pointers/README.MD`
  - `system/x11/Readme.md`

Use this baseline to prioritize docs synchronization before high-impact renames.

## Safety Notes
- never run destructive git commands for normalization workflows
- prefer incremental commits per rename/documentation batch
- if unexpected unrelated changes appear, stop and ask for direction

## Suggested Commit Split
1. `docs: normalize README filenames and fix links`
2. `refactor: standardize directory naming`
3. `docs: regenerate root module index`

## Example Prompts To Invoke This Skill
- `/codebase-standardization Padronize diretorios para kebab-case e atualize o README raiz com os modulos reais.`
- `/codebase-standardization Corrija links quebrados no README e normalize todos os Readme.md para README.md.`
- `/codebase-standardization Gere um plano de renomeacao seguro usando git mv e validacoes por etapa.`
