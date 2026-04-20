---
name: codebase-standardization
description: 'Analisa a diff da branch e do working tree nao commitado para padronizar nomes de diretorios, documentacao e README conforme a estrutura real do projeto. Use para: analisar diff da branch, padronizar projeto em andamento, alinhar arquivos nao commitados, corrigir links e sincronizar indice do README.'
argument-hint: 'Base da diff + escopo + convencao (ex.: main + somente nao commitado + kebab-case)'
user-invocable: true
---

# Codebase Standardization (Diff-Aware + Uncommitted Work)

## Outcome
This skill applies a repeatable workflow to:
- analyze branch diff and local uncommitted changes before editing
- standardize naming and directory structure using a chosen convention
- normalize documentation and README links to match the real filesystem
- synchronize root README index with the actual project modules
- preserve in-progress work while reducing structural drift

## When To Use
Use this skill when you need one of these outcomes:
- "analise a diff da branch"
- "padronize meu projeto nao commitado"
- "alinhe o que estou trabalhando com a estrutura do projeto"
- "padronizar nomes de diretorios"
- "normalizar documentacao"
- "atualizar README com o codebase"
- "corrigir links quebrados no README"
- "alinhar estrutura de pastas e indice"

## Input Required
Collect these inputs before changing files:
1. Diff base and scope:
- Option A: compare with default branch (`main`)
- Option B: compare with a user-specified base (`release/x`, `HEAD~N`)
- Option C: process only local uncommitted changes (staged + unstaged + untracked)

2. Target naming convention:
- Option A: `lower-kebab-case` (recommended for cross-platform consistency)
- Option B: keep current top-level names and only normalize docs/links

3. Scope of renames:
- Option A: full repo
- Option B: only paths touched in diff/uncommitted changes
- Option C: only top-level folders
- Option D: no folder renames, docs/readme sync only

4. README policy:
- Option A: regenerate index table from filesystem
- Option B: keep curated table and only fix invalid links

5. Safety mode:
- Option A: docs-first (lowest risk)
- Option B: docs + selective renames (medium risk)
- Option C: full refactor (highest impact)

## Workflow

### 1. Analyze Branch Diff and Working Tree
Build an explicit change map before modifying anything:
- branch delta: files changed relative to base branch
- local delta: staged, unstaged, and untracked files
- rename/delete events already present in diff

Use these checks:
- `git status --short`
- `git diff --name-status <base>...HEAD`
- `git diff --name-status`
- `git diff --cached --name-status`

Decision point:
- if no diff and clean working tree: run structural audit mode only
- if dirty working tree: prioritize non-destructive, incremental updates

### 2. Create Structure Snapshot
Generate objective inventory of repository state:
- all top-level directories
- all README-like files (`README.md`, `Readme.md`, `README.MD`)
- naming style distribution
- root README links and their resolution status

Use these checks:
- `Get-ChildItem -Recurse -Directory`
- `Get-ChildItem -Recurse -File | Where-Object { $_.Name -imatch '^readme(\\..+)?$' }`
- parse root README markdown links and test each local path

### 3. Detect Drift and Inconsistencies
Classify issues in two buckets:

Bucket A: issues inside diff/uncommitted scope
- must be fixed in this run

Bucket B: issues outside current scope
- report as backlog without forcing unrelated edits

Identify and classify concrete problems:
- missing target paths from README links
- case mismatches between link and actual folder path
- duplicate naming concepts (example: singular/plural or legacy aliases)
- mixed naming conventions in same level
- non-standard README filenames (`Readme.md`, `README.MD`)

### 4. Decide Migration Strategy
Branch by impact:

If there are many external references or high break risk:
- prefer docs-first strategy
- keep directory names for now
- fix README links to real paths

If you can perform structural refactor safely in current scope:
- create rename map and migrate folders with `git mv` (diff-scoped first)
- update references in docs/source
- regenerate README index from live filesystem

If rename is case-only on Windows:
- use two-step rename to avoid case-insensitive collisions
- pattern: `git mv Path TempName` then `git mv TempName path`

If target name collides with an existing path:
- do not auto-rename
- choose a non-conflicting canonical name and confirm with user

If user asked for uncommitted-only processing:
- do not broaden edits to unrelated files without explicit approval

### 5. Apply Renames and Normalization Safely
Rules:
- always use `git mv` (preserve history)
- rename one logical group at a time
- after each batch, run quick link/reference checks
- never use destructive git commands to force a clean state
- never revert unrelated user edits

For docs files:
- normalize all README variants to exactly `README.md`
- ensure each documented module has one entry-point README

### 6. Update Documentation Links
Update links in:
- root README
- module README files
- docs indexes and navigation sections

Link policy:
- use repository-relative links
- match exact path casing to avoid cross-platform breakage
- remove or replace legacy links pointing to removed modules

### 7. Synchronize Root README With Real Codebase
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

### 8. Validate Completion
Completion checks (all must pass):
1. no missing local links in root README
2. no case-mismatch links in root README
3. all README filenames are exactly `README.md` in processed scope
4. no stale references to removed/renamed paths (`rg` search) in processed scope
5. root README index matches actual repository modules
6. diff summary clearly states what was fixed vs deferred

## Branching Logic Summary
- If branch diff is large and uncommitted work is sensitive: run docs-first or diff-scoped mode.
- If branch diff is small and cohesive: allow selective renames + docs sync.
- If collisions or risky renames appear: stop and request naming decision.
- If working tree is clean: full-repo audit and normalization is allowed.

## Quality Gates
A standardization run is complete only when:
- path naming policy is consistently applied in selected scope
- documentation paths resolve on case-sensitive environments
- no table entry points to non-existing directories
- renamed paths have updated references everywhere relevant
- branch/uncommitted analysis is reported explicitly before and after changes
- unresolved out-of-scope issues are listed separately as follow-up backlog

## Repository Baseline Observed (C-Codebase)
This repository currently shows:
- historical drift between documented module names and real filesystem paths
- mixed naming conventions from legacy and newer folders
- previous case mismatch and stale link issues in root and module READMEs

Use this baseline to prioritize docs synchronization before high-impact renames.

## Safety Notes
- never run destructive git commands for normalization workflows
- prefer incremental commits per rename/documentation batch
- if unexpected unrelated changes appear, stop and ask for direction
- when user asks to process non-committed work, treat existing dirty files as first-class scope

## Suggested Commit Split
1. `chore: analyze branch diff and working-tree drift`
2. `docs: normalize README filenames and fix links`
3. `refactor: standardize directory naming (scoped)`
4. `docs: regenerate root module index`

## Output Contract
Every run should report:
1. Diff base used and scope processed
2. Files changed in this run
3. Validation results (links, naming, README index)
4. Deferred issues outside requested scope

## Example Prompts To Invoke This Skill
- `/codebase-standardization Padronize diretorios para kebab-case e atualize o README raiz com os modulos reais.`
- `/codebase-standardization Corrija links quebrados no README e normalize todos os Readme.md para README.md.`
- `/codebase-standardization Gere um plano de renomeacao seguro usando git mv e validacoes por etapa.`
- `/codebase-standardization Analise a diff da branch e padronize o projeto nao commitado com a estrutura atual.`
- `/codebase-standardization Compare com main, aplique apenas em arquivos nao commitados e sincronize o README.`
