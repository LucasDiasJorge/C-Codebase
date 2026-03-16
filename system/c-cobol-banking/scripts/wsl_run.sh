#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

make reset-data
make run
