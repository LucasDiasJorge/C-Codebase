---
name: diff-aware-standardization
description: 'Analyze branch diff and uncommitted changes, then standardize directories, docs, and root README to match real project structure. Use for branch drift cleanup, in-progress standardization, and link/index synchronization.'
argument-hint: 'Base branch + scope + naming convention (ex.: main + uncommitted-only + lower-kebab-case)'
user-invocable: true
---

# Diff-Aware Codebase Standardization

## Outcome
This skill applies a repeatable workflow to:
- analyze branch diff before changing files
- process local staged, unstaged, and untracked work safely
- standardize naming and structure in a controlled scope
- synchronize docs and README with the real filesystem
- report what was fixed now vs deferred for later

## When To Use
Use this skill when you need one of these outcomes:
- "analisar diff da branch"
- "padronizar projeto nao commitado"
- "alinhar estrutura com o que estou trabalhando"
- "corrigir links quebrados na documentacao"
- "sincronizar README com modulos reais"

## Required Inputs
Collect these inputs before editing:
1. Diff base:
- Option A: default branch (main)
- Option B: user-provided base (release/x, HEAD~N)
- Option C: uncommitted-only (working tree focus)

2. Scope:
- Option A: full repository
- Option B: only changed paths in diff
- Option C: only uncommitted files
- Option D: docs-only and README sync

3. Naming policy:
- Option A: lower-kebab-case
- Option B: preserve top-level names, normalize docs/links only

4. README policy:
- Option A: regenerate module index from filesystem
- Option B: keep curated table and only fix invalid paths

5. Risk mode:
- Option A: docs-first (lowest risk)
- Option B: selective refactor (medium risk)
- Option C: full refactor (highest impact)

## Procedure

### 1. Build Change Map
Collect objective change context first:
- branch diff (`git diff --name-status <base>...HEAD`)
- unstaged diff (`git diff --name-status`)
- staged diff (`git diff --cached --name-status`)
- working tree summary (`git status --short`)

Decision point:
- If working tree is dirty, prefer incremental and non-destructive updates.
- If clean, full audit mode is allowed.

### 2. Build Structure Snapshot
Collect current repository structure:
- top-level directories
- README-like files (`README.md`, `Readme.md`, `README.MD`)
- naming style distribution
- root README link validity

### 3. Classify Issues by Scope
Split issues into two buckets:
- Bucket A (in-scope): must fix now
- Bucket B (out-of-scope): log as backlog

Issue types to classify:
- missing link targets
- case mismatch links
- mixed naming conventions
- stale module names in README
- non-standard README filename variants

### 4. Choose Migration Strategy
- Docs-first when risk is high or branch is sensitive.
- Selective renames for changed paths when safe.
- Full rename/refactor only with clear user intent.

If renaming on Windows with case-only changes:
- use two-step rename (`git mv old temp`, then `git mv temp new`).

If path collision is detected:
- do not auto-rename; request naming decision.

### 5. Apply Changes Safely
Rules:
- use `git mv` for path renames
- process one logical group at a time
- verify links after each batch
- do not revert unrelated user edits
- do not use destructive git commands

### 6. Synchronize Documentation
Update links in:
- root README
- module README files
- docs indexes/navigation pages

Policy:
- repository-relative paths
- exact case matching for cross-platform reliability
- remove/replace stale legacy references

### 7. Synchronize Root README
Ensure module table matches real top-level directories:
1. list current modules
2. merge with curated labels/descriptions
3. regenerate contiguous numbering
4. replace stale rows

### 8. Validate and Report
Run validation checks and publish a concise report.

## Decision Logic
- Large diff + dirty tree: docs-first or changed-path-only mode.
- Small cohesive diff: selective rename + docs sync.
- Clean tree: allow full repository normalization.
- Rename collisions or risky moves: pause and request confirmation.

## Completion Checks
A run is complete only if all pass in processed scope:
1. no missing local links in root README
2. no case-mismatch local links in root README
3. README filenames normalized to `README.md`
4. no stale references to renamed paths in processed files
5. root README module index matches actual top-level modules
6. output report separates fixed vs deferred items

## Safety Rules
- Never use destructive git commands.
- Never revert unrelated changes.
- Prefer incremental batches and explicit verification.
- If unexpected unrelated modifications appear mid-run, stop and ask for direction.

## Output Contract
Every execution should report:
1. diff base and chosen scope
2. files changed in this run
3. validation results (links, naming, README index)
4. deferred out-of-scope issues

## Example Prompts
- `/diff-aware-standardization Analise a diff da branch e padronize o projeto nao commitado com a estrutura atual.`
- `/diff-aware-standardization Compare com main e aplique apenas em arquivos nao commitados.`
- `/diff-aware-standardization Corrija links/docs e sincronize o README sem renomear diretorios.`
- `/diff-aware-standardization Gere plano de padronizacao por lotes com validacao apos cada lote.`
