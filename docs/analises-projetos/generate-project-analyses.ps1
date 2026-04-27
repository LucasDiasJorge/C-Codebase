Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$root = Get-Location
$analysisDir = Join-Path $root "docs\analises-projetos"
New-Item -ItemType Directory -Path $analysisDir -Force | Out-Null
$analysisDirPath = [System.IO.Path]::GetFullPath($analysisDir)

$profiles = @{
    "beginner" = @{
        Scope = "Trilha de entrada para estudantes com foco em manipulacao basica de strings e leitura de README orientado a exercicios."
        Domain = "Fundamentos de strings, comparacao de prefixos e remocao de caracteres in-place."
        Learning = "Excelente para iniciar ponteiros sobre arrays de char e reforcar terminador nulo."
        Priorities = @(
            "Adicionar exemplos compilaveis em C no proprio modulo para reduzir dependencia cruzada de outras pastas.",
            "Incluir casos de teste de borda para string vazia, caracteres repetidos e entrada nula.",
            "Padronizar nomes de pasta para minusculas e referencias consistentes nos READMEs."
        )
        BaseRisks = @(
            "Material majoritariamente documental pode dificultar validacao automatica.",
            "Ausencia de build script local reduz reproducibilidade para iniciantes."
        )
        Related = @("fundamentals", "function", "filesystem")
    }
    "conversor-pdf" = @{
        Scope = "Modulo tematico de conversao HTML para PDF, orientado por integracao de ferramenta externa."
        Domain = "Execucao de comandos de sistema, composicao de linha de comando e tratamento de retorno."
        Learning = "Bom exemplo de ponte entre C e utilitarios CLI sem criar dependencia de biblioteca pesada no codigo."
        Priorities = @(
            "Adicionar validacao de path e escape robusto para argumentos em system().",
            "Criar versao alternativa usando biblioteca nativa para evitar shell injection.",
            "Documentar matriz de compatibilidade por SO e formato de saida."
        )
        BaseRisks = @(
            "Dependencia externa (wkhtmltopdf) pode quebrar em ambientes sem setup previo.",
            "Uso de system() exige cuidado com seguranca e quoting de parametros."
        )
        Related = @("patterns", "screenshot-project", "docs")
    }
    "cross-compilation" = @{
        Scope = "Projeto estruturado para build multiplataforma Linux/Windows com foco em portabilidade e automacao."
        Domain = "Toolchains MinGW, CMake/Make, scripts de setup e testes de executavel Windows via Wine."
        Learning = "Referencia forte para engenharia de build em C com multiplos alvos."
        Priorities = @(
            "Adicionar pipeline CI para linux, windows-64 e windows-32 com artefatos de release.",
            "Cobrir testes com validacao de comportamento identico entre plataformas.",
            "Introduzir estrategia de versionamento de toolchain para evitar drift de ambiente."
        )
        BaseRisks = @(
            "Complexidade de matriz de build aumenta custo de manutencao.",
            "Dependencia de ferramentas externas pode gerar falhas intermitentes em novos ambientes."
        )
        Related = @("system", "screenshot-project", "networking")
    }
    "data-structures" = @{
        Scope = "Colecao de estruturas de dados e serializacao com exemplos praticos de hash, hashtable e JSON."
        Domain = "Modelagem de dados, funcoes de hash, listas encadeadas e parse JSON em C."
        Learning = "Modulo central para consolidar estruturas dinamicas e custo computacional em C."
        Priorities = @(
            "Criar suite de testes unitarios para operacoes de insert, lookup e delete.",
            "Adicionar verificacao de memoria com AddressSanitizer e Valgrind na documentacao.",
            "Formalizar contratos de API (ownership de ponteiros e regras de liberacao)."
        )
        BaseRisks = @(
            "Estruturas dinamicas sem testes consistentes podem esconder leaks e use-after-free.",
            "Presenca de artefato binario versionado indica oportunidade de limpeza de repositorio."
        )
        Related = @("json", "memory", "fundamentals")
    }
    "docs" = @{
        Scope = "Hub de documentacao, links de referencia e relatorios analiticos do repositorio."
        Domain = "Curadoria tecnica e organizacao de conhecimento."
        Learning = "Apoia navegacao e acelera onboarding de contribuidores."
        Priorities = @(
            "Criar indice rastreavel por modulo com status de maturidade e comandos de build.",
            "Versionar padrao de template unico para READMEs de subprojetos.",
            "Automatizar validacao de links e consistencia de caminhos."
        )
        BaseRisks = @(
            "Documentacao desatualizada pode divergir da estrutura real do codigo.",
            "Sem automacao de verificacao, links quebrados tendem a crescer com o tempo."
        )
        Related = @("README.md", "cross-compilation", "fundamentals")
    }
    "files" = @{
        Scope = "Modulo focado em operacoes de remocao de arquivo e semantica de erro em nivel de sistema."
        Domain = "unlink/remove, errno e permissoes em sistemas POSIX."
        Learning = "Bom ponto de partida para entender IO de baixo nivel e tratamento de falha."
        Priorities = @(
            "Adicionar exemplo compilavel local para evitar modulo apenas documental.",
            "Cobrir cenarios de erro com arquivos inexistentes, sem permissao e path de diretorio.",
            "Comparar comportamento em Linux e Windows via wrappers portaveis."
        )
        BaseRisks = @(
            "Falta de codigo local reduz valor pratico imediato.",
            "Operacoes destrutivas sem sandbox podem causar uso acidental indevido."
        )
        Related = @("filesystem", "system", "fundamentals")
    }
    "filesystem" = @{
        Scope = "Conjunto amplo de exemplos de IO de arquivos e diretorios, incluindo contador de palavras."
        Domain = "Leitura, escrita, estatisticas, regex e utilitarios de manipulacao de path."
        Learning = "Cobertura forte para transicao entre stdio e chamadas mais proximas do sistema."
        Priorities = @(
            "Criar executavel agregador por submodulo com Makefile local.",
            "Padronizar tratamento de erro e retorno em todos os exemplos.",
            "Adicionar testes de regressao para parser de arquivos e contador de palavras."
        )
        BaseRisks = @(
            "Diferencas de API entre POSIX e Windows podem limitar portabilidade.",
            "Sem harness de teste, alteracoes em parser podem introduzir regressao silenciosa."
        )
        Related = @("files", "memory", "networking")
    }
    "function" = @{
        Scope = "Modulo guia para funcoes avancadas, com ponte para ponteiros de funcao e variadicas."
        Domain = "Design de API em C, callbacks e stdarg."
        Learning = "Apoia entendimento de interfaces flexiveis em C sem recursos de linguagem orientada a objetos."
        Priorities = @(
            "Consolidar exemplos em um unico executavel demonstrativo com entradas previsiveis.",
            "Documentar undefined behavior comum em variadicas e type promotion.",
            "Adicionar exercicios com ponteiros de funcao para dispatch table."
        )
        BaseRisks = @(
            "Modulo depende de conteudo de fundamentals para execucao real.",
            "Sem testes, erros de assinatura de callback podem passar despercebidos."
        )
        Related = @("fundamentals", "patterns", "memory")
    }
    "fundamentals" = @{
        Scope = "Maior trilha didatica do repositorio com cobertura de beginner, enum, union, preprocessors e funcoes."
        Domain = "Base da linguagem C com progressao de nivel iniciante para intermediario/avancado."
        Learning = "Nucleo pedagogico principal do repositorio, com grande volume de exemplos em C."
        Priorities = @(
            "Criar trilha oficial de estudo por ordem de complexidade e prerequisitos.",
            "Introduzir testes automatizados minimos para cada subpasta com codigo executavel.",
            "Padronizar estilo de codigo e nomenclatura entre todos os submodulos."
        )
        BaseRisks = @(
            "Escopo amplo aumenta risco de inconsistencias de estilo e padrao didatico.",
            "Ausencia de build unificado dificulta validar tudo em lote."
        )
        Related = @("beginner", "function", "memory")
    }
    "json" = @{
        Scope = "Hub de referencia para manipulacao de JSON, direcionando para implementacoes em data-structures/json."
        Domain = "Modelagem de objetos JSON, parse e serializacao."
        Learning = "Facilita navegacao para praticas de JSON em C sem inflar o modulo raiz."
        Priorities = @(
            "Unificar caminho de exemplos para reduzir duplicidade entre pastas json e data-structures/json.",
            "Adicionar benchmark comparando biblioteca externa e implementacao manual.",
            "Incluir testes de robustez com JSON invalido e grande volume de dados."
        )
        BaseRisks = @(
            "Conteudo apenas documental no topo pode confundir expectativa de codigo executavel.",
            "Duplicidade de estrutura pode gerar divergencia de manutencao."
        )
        Related = @("data-structures", "networking", "memory")
    }
    "memory" = @{
        Scope = "Colecao especializada em gerenciamento de memoria, ponteiros e tecnicas de alocacao."
        Domain = "malloc, pools, memset, ponteiros avancados, uso e perfil de memoria."
        Learning = "Modulo critico para raciocinio de baixo nivel e prevencao de bugs severos em C."
        Priorities = @(
            "Adicionar cenario de teste para memory leaks, double free e use-after-free.",
            "Documentar ownership e ciclo de vida de cada bloco alocado nos exemplos.",
            "Criar comparativos de performance entre alocacao tradicional e memory pool."
        )
        BaseRisks = @(
            "Topico de alto risco para UB exige validacao automatica constante.",
            "Exemplos avancados sem sanitizers podem mascarar defeitos."
        )
        Related = @("fundamentals", "data-structures", "system")
    }
    "miscellaneous" = @{
        Scope = "Colecao de utilitarios didaticos variados para treino rapido de logica em C."
        Domain = "Algoritmos curtos, strings, random, deteccao de SO e exercicios diversos."
        Learning = "Bom ambiente de pratica incremental para estudantes entre modulos maiores."
        Priorities = @(
            "Adicionar indice com objetivo de cada utilitario e nivel de dificuldade.",
            "Criar scripts de compilacao em lote para todos os exemplos pequenos.",
            "Separar exemplos de demonstracao de exemplos prontos para reutilizacao."
        )
        BaseRisks = @(
            "Escopo heterogeneo pode reduzir coesao e descoberta por assunto.",
            "Sem testes, exemplos curtos podem acumular pequenos erros de comportamento."
        )
        Related = @("patterns", "fundamentals", "filesystem")
    }
    "network" = @{
        Scope = "Entrada documental para comunicacao de rede, com foco em init-variable e envio de arquivo."
        Domain = "HTTP basico com libcurl e operacoes iniciais de transferencia."
        Learning = "Introduz conceitos de IO de rede antes da trilha mais extensa em networking."
        Priorities = @(
            "Adicionar codigo executavel local para consolidar modulo de entrada.",
            "Padronizar dependencia de libcurl com instrucoes por plataforma.",
            "Conectar explicitamente este modulo aos exemplos avancados de networking."
        )
        BaseRisks = @(
            "Conteudo predominantemente documental pode gerar baixa verificabilidade.",
            "Duplicidade de tema com networking precisa de fronteira clara."
        )
        Related = @("networking", "json", "cross-compilation")
    }
    "networking" = @{
        Scope = "Trilha principal de programacao de rede com clientes, servidores, HTTP e exemplos de backend."
        Domain = "Sockets, protocolos, IO bloqueante, stream HTTP e integracao com APIs."
        Learning = "Modulo de alto valor para evoluir de C basico para sistemas conectados."
        Priorities = @(
            "Adicionar testes de integracao para cenarios cliente/servidor com timeout controlado.",
            "Padronizar validacao de entrada e limites de buffer em todos os handlers.",
            "Documentar politicas de seguranca minima para exemplos HTTP e socket request."
        )
        BaseRisks = @(
            "Codigo de rede sem hardening pode conter riscos de seguranca e travamento.",
            "Grande numero de exemplos dificulta manter consistencia de erro e logging."
        )
        Related = @("network", "system", "json")
    }
    "optimization-tips" = @{
        Scope = "Repositorio de boas praticas de performance, com foco em localidade de dados."
        Domain = "Cache locality, acesso de memoria e impacto de padrao de iteracao."
        Learning = "Excelente para ligar teoria de arquitetura de computador com codigo C real."
        Priorities = @(
            "Adicionar benchmark executavel com medicao repetivel e variancia.",
            "Comparar resultados com diferentes tamanhos de matriz e flags de compilador.",
            "Expandir modulo com tecnicas como blocking e loop interchange."
        )
        BaseRisks = @(
            "Sem codigo no topo, o aprendizado depende de navegacao manual ate subpastas.",
            "Sem medicao padronizada, conclusoes de performance podem variar por maquina."
        )
        Related = @("patterns", "memory", "fundamentals")
    }
    "patterns" = @{
        Scope = "Colecao extensa de padroes praticos e exemplos aplicados em C."
        Domain = "Observer, callback, debugging, optimizacao e utilitarios diversos."
        Learning = "Modulo ponte entre fundamentos e arquitetura de codigo orientada a padroes."
        Priorities = @(
            "Eliminar artefatos compilados do versionamento e reforcar .gitignore local.",
            "Separar exemplos experimentais de exemplos recomendados para estudo.",
            "Criar tabela comparativa de padroes com quando usar e quando evitar."
        )
        BaseRisks = @(
            "Volume alto e heterogeneo aumenta risco de duplicidade e drift de qualidade.",
            "Presenca de binarios versionados reduz higiene do repositorio."
        )
        Related = @("miscellaneous", "optimization-tips", "function")
    }
    "preprocessors" = @{
        Scope = "Modulo didatico de preprocessador com samples curtos e foco em #define e includes."
        Domain = "Macros, substituicao textual e boas praticas de preprocessamento."
        Learning = "Apoia base de compilacao e metaprogramacao leve em C."
        Priorities = @(
            "Adicionar exemplos compilaveis no proprio modulo para cada sample.",
            "Padronizar naming e referencias cruzadas com fundamentals/preprocessors.",
            "Incluir secao sobre riscos de macros sem parenteses e side effects."
        )
        BaseRisks = @(
            "Duplicidade parcial com fundamentals/preprocessors pode confundir trilha oficial.",
            "Falta de codigo no topo dificulta validacao automatizada."
        )
        Related = @("fundamentals", "function", "docs")
    }
    "screenshot-project" = @{
        Scope = "Projeto utilitario de captura de tela com implementacoes separadas para X11 e WinAPI."
        Domain = "Integracao com APIs nativas de SO e geracao de imagem sem dependencias pesadas."
        Learning = "Bom estudo de portabilidade real em IO grafico de baixo nivel."
        Priorities = @(
            "Adicionar script de build cruzado para Linux e Windows no mesmo fluxo.",
            "Implementar testes de smoke para validar existencia e dimensao da imagem gerada.",
            "Documentar limitacoes por ambiente (Wayland, permissoes, multi-monitor)."
        )
        BaseRisks = @(
            "Dependencia de APIs especificas pode quebrar em ambientes graficos diferentes.",
            "Sem testes automatizados, regressao de formato de imagem passa despercebida."
        )
        Related = @("cross-compilation", "system", "conversor-pdf")
    }
    "system" = @{
        Scope = "Colecao de integracoes de baixo nivel com assembly, serial, USB, tempo e componentes de sistema."
        Domain = "APIs de SO, dispositivos, interoperabilidade C/Assembly e C/COBOL."
        Learning = "Modulo avancado para aproximar C de contexto real de sistemas e legado."
        Priorities = @(
            "Separar exemplos por nivel de privilegio (usuario comum vs root).",
            "Adicionar guia de seguranca para operacoes com mount, serial e chamadas sensiveis.",
            "Padronizar build e testes minimos para cada submodulo de sistema."
        )
        BaseRisks = @(
            "Operacoes de sistema podem exigir privilegios e causar efeitos colaterais no host.",
            "Diversidade de submodulos aumenta risco de inconsistencias de manutencao."
        )
        Related = @("usb", "time", "cross-compilation")
    }
    "time" = @{
        Scope = "Modulo direcionado para conversao e tratamento de timestamps em C."
        Domain = "time_t, struct tm, strftime/strptime e fusos horarios."
        Learning = "Bom reforco para manipulacao temporal e interoperabilidade de formatos."
        Priorities = @(
            "Adicionar exemplos executaveis no topo para reduzir dependencia de subpastas.",
            "Cobrir casos de timezone, DST e datas invalidas com testes de regressao.",
            "Alinhar este modulo com system/time para evitar redundancia de manutencao."
        )
        BaseRisks = @(
            "Duplicidade de conteudo com system/time pode gerar divergencia.",
            "Manipulacao de tempo sem testes de borda pode causar erros sutis."
        )
        Related = @("system", "fundamentals", "memory")
    }
    "usb" = @{
        Scope = "Modulo focado em montagem de USB por syscall e documentacao de operacao privilegiada."
        Domain = "mount/umount, permissao de root e manipulacao de sistema de arquivos."
        Learning = "Exemplo util para entender fronteira entre programa C e administracao de sistema."
        Priorities = @(
            "Adicionar exemplo de desmontagem e verificacao de integridade apos copia.",
            "Documentar modo seguro para testes sem impactar dispositivos reais.",
            "Unificar narrativa com system/usb para evitar duplicidade de conteudo."
        )
        BaseRisks = @(
            "Operacoes de mount exigem cuidado para nao afetar o host do desenvolvedor.",
            "Modulo no topo e modulo em system/usb podem divergir com o tempo."
        )
        Related = @("system", "filesystem", "files")
    }
}

function Get-Profile([string]$projectName) {
    if ($profiles.ContainsKey($projectName)) {
        return $profiles[$projectName]
    }

    return @{
        Scope = "Modulo de estudo em C sem perfil especificado no gerador."
        Domain = "Conceitos gerais de programacao em C."
        Learning = "Contribui para repertorio didatico do repositorio."
        Priorities = @(
            "Padronizar README e instrucoes de build.",
            "Adicionar testes minimos para comportamento esperado.",
            "Documentar limites e escopo do modulo."
        )
        BaseRisks = @("Escopo nao catalogado no gerador de analise.")
        Related = @()
    }
}

function Get-MaturityLabel([double]$score) {
    if ($score -ge 4.3) { return "Alta" }
    if ($score -ge 3.4) { return "Media-Alta" }
    if ($score -ge 2.5) { return "Media" }
    if ($score -ge 1.8) { return "Media-Baixa" }
    return "Baixa"
}

function Get-RegexCount([string]$text, [string]$pattern) {
    if ([string]::IsNullOrWhiteSpace($text)) {
        return 0
    }

    return ([regex]::Matches($text, $pattern, [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)).Count
}

function Get-EvidencePaths([array]$sourceInfo, [string]$pattern, [int]$max = 4) {
    $hits = @()

    foreach ($item in $sourceInfo) {
        if ([regex]::IsMatch($item.Text, $pattern, [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)) {
            $hits += $item.Path
        }
    }

    return @($hits | Select-Object -Unique | Select-Object -First $max)
}

function To-Bullets([array]$items, [string]$emptyMessage) {
    $safeItems = @($items)
    if ($safeItems.Count -eq 0) {
        return "- " + $emptyMessage
    }

    return ($safeItems | ForEach-Object { "- " + $_ }) -join "`n"
}

$projects = Get-ChildItem -Directory | Where-Object { $_.Name -ne ".github" } | Sort-Object Name
$indexRows = @()

foreach ($project in $projects) {
    $name = $project.Name
    $profile = Get-Profile $name

    $files = @(
        Get-ChildItem $project.FullName -Recurse -File -ErrorAction SilentlyContinue |
            Where-Object { -not $_.FullName.StartsWith($analysisDirPath, [System.StringComparison]::OrdinalIgnoreCase) }
    )
    $cFiles = @($files | Where-Object { $_.Extension -eq ".c" })
    $hFiles = @($files | Where-Object { $_.Extension -eq ".h" })
    $mdFiles = @($files | Where-Object { $_.Extension -eq ".md" })
    $readmes = @($files | Where-Object { $_.Name -match "^(?i)readme(\..+)?\.md$|^(?i)readme\.md$" })
    $buildFiles = @($files | Where-Object { $_.Name -in "Makefile", "CMakeLists.txt" -or $_.Name -match "^toolchain-.*\.cmake$" })
    $scriptFiles = @($files | Where-Object { $_.Extension -in ".sh", ".ps1", ".bat" })
    $artifactFiles = @($files | Where-Object { $_.Extension -in ".out", ".o", ".bin", ".exe" -or $_.Name -eq "a.out" })
    $testFiles = @($files | Where-Object { $_.Name -match "(?i)test" -and $_.Extension -in ".c", ".h", ".sh" })

    $sourceFiles = @($cFiles + $hFiles)
    $sourceInfo = @()
    $loc = 0
    $allCodeTextBuilder = New-Object System.Text.StringBuilder

    foreach ($source in $sourceFiles) {
        $sourceText = ""
        try {
            $sourceText = Get-Content $source.FullName -Raw -ErrorAction Stop
        } catch {
            $sourceText = ""
        }

        $lineCount = if ([string]::IsNullOrEmpty($sourceText)) {
            0
        } else {
            ($sourceText -split "`r?`n").Count
        }

        $loc += $lineCount
        [void]$allCodeTextBuilder.AppendLine($sourceText)

        $sourceInfo += [PSCustomObject]@{
            Path = $source.FullName.Substring($root.Path.Length + 1).Replace('\', '/')
            Lines = $lineCount
            Text = $sourceText
        }
    }

    $allCodeText = $allCodeTextBuilder.ToString()

    $functionCount = Get-RegexCount $allCodeText '(?m)^\s*(?:static\s+)?(?:inline\s+)?(?:const\s+)?[a-zA-Z_][\w\s\*]*\s+[a-zA-Z_]\w*\s*\([^;]*\)\s*\{'
    $controlFlowCount = Get-RegexCount $allCodeText '\b(if|switch|for|while|do)\b'
    $todoCount = Get-RegexCount $allCodeText '\b(TODO|FIXME|HACK|XXX)\b'

    $riskyPatterns = [ordered]@{
        "gets" = '(?<!\w)gets\s*\('
        "strcpy" = '(?<!\w)strcpy\s*\('
        "strcat" = '(?<!\w)strcat\s*\('
        "sprintf" = '(?<!\w)sprintf\s*\('
        "scanf" = '(?<!\w)scanf\s*\('
        "system" = '(?<!\w)system\s*\('
    }

    $riskyCallCounts = [ordered]@{}
    $riskyEvidence = [ordered]@{}

    foreach ($key in $riskyPatterns.Keys) {
        $pattern = $riskyPatterns[$key]
        $riskyCallCounts[$key] = Get-RegexCount $allCodeText $pattern
        $riskyEvidence[$key] = @(Get-EvidencePaths -sourceInfo $sourceInfo -pattern $pattern -max 4)
    }

    $mallocCount = Get-RegexCount $allCodeText '(?<!\w)malloc\s*\('
    $callocCount = Get-RegexCount $allCodeText '(?<!\w)calloc\s*\('
    $reallocCount = Get-RegexCount $allCodeText '(?<!\w)realloc\s*\('
    $freeCount = Get-RegexCount $allCodeText '(?<!\w)free\s*\('
    $allocationCount = $mallocCount + $callocCount + $reallocCount
    $releaseCount = $freeCount

    $windowsIncludeCount = Get-RegexCount $allCodeText '#\s*include\s*<windows\.h>'
    $posixIncludeCount = Get-RegexCount $allCodeText '#\s*include\s*<(unistd\.h|sys/socket\.h|pthread\.h|termios\.h|sys/mount\.h|dirent\.h|netdb\.h|arpa/inet\.h)>'
    $curlIncludeCount = Get-RegexCount $allCodeText '#\s*include\s*<curl/curl\.h>'
    $regexIncludeCount = Get-RegexCount $allCodeText '#\s*include\s*<regex\.h>'

    $apiRiskTotal = 0
    foreach ($value in $riskyCallCounts.Values) {
        $apiRiskTotal += [int]$value
    }

    $platformSignals = @()
    if ($windowsIncludeCount -gt 0) { $platformSignals += "Windows API includes: $windowsIncludeCount" }
    if ($posixIncludeCount -gt 0) { $platformSignals += "POSIX/network includes: $posixIncludeCount" }
    if ($curlIncludeCount -gt 0) { $platformSignals += "libcurl includes: $curlIncludeCount" }
    if ($regexIncludeCount -gt 0) { $platformSignals += "regex includes: $regexIncludeCount" }
    if ($platformSignals.Count -eq 0) { $platformSignals += "Sem sinal forte de API de plataforma no codigo C/H deste modulo." }

    $topSourceCandidates = @($sourceInfo | Where-Object {
        $_.Path -notmatch '(^|/)(compiler-example|generated|dist)/' -and
        $_.Path -notmatch '(^|/)(fast\.c)$'
    })
    $topSourceItems = @($topSourceCandidates | Sort-Object Lines -Descending | Select-Object -First 8)

    $findings = @()

    if ($riskyCallCounts["gets"] -gt 0) {
        $findings += "[Critico] Uso de gets detectado ($($riskyCallCounts["gets"]) ocorrencia(s)); remocao urgente recomendada."
    }
    if (($riskyCallCounts["strcpy"] + $riskyCallCounts["strcat"] + $riskyCallCounts["sprintf"]) -gt 0) {
        $findings += "[Alto] APIs de manipulacao de string potencialmente inseguras detectadas: strcpy=$($riskyCallCounts["strcpy"]), strcat=$($riskyCallCounts["strcat"]), sprintf=$($riskyCallCounts["sprintf"])."
    }
    if ($riskyCallCounts["system"] -gt 0) {
        $findings += "[Alto] Chamada system() detectada ($($riskyCallCounts["system"]) ocorrencia(s)); revisar sanitizacao de input e quoting."
    }
    if ($allocationCount -gt 0 -and $releaseCount -eq 0) {
        $findings += "[Alto] Alocacao dinamica detectada sem chamada de free no mesmo escopo de modulo (alloc=$allocationCount, free=$releaseCount)."
    } elseif ($allocationCount -gt 0 -and $releaseCount -lt [math]::Floor($allocationCount / 2)) {
        $findings += "[Medio] Desbalanco entre chamadas de alocacao e liberacao (alloc=$allocationCount, free=$releaseCount); validar ownership e ciclo de vida."
    }
    if ($todoCount -gt 0) {
        $findings += "[Medio] Marcadores TODO/FIXME/HACK encontrados ($todoCount)."
    }
    if ($functionCount -gt 0 -and $testFiles.Count -eq 0) {
        $findings += "[Medio] Funcoes detectadas sem evidencias de testes nomeados no modulo (funcoes=$functionCount)."
    }
    if ($findings.Count -eq 0) {
        $findings += "[Info] Nao foram detectados sinais criticos por heuristica estatica; manter validacao com compilacao e testes."
    }

    $highSeverityFindings = @($findings | Where-Object { $_ -match '^\[(Critico|Alto)\]' }).Count

    $subprojects = @()
    foreach ($readme in $readmes) {
        $relativeDir = (Split-Path $readme.FullName -Parent).Substring($project.FullName.Length).TrimStart([char]'\')
        if ([string]::IsNullOrWhiteSpace($relativeDir)) {
            $subprojects += $name
        } else {
            $subprojects += ($name + "/" + $relativeDir.Replace('\', '/'))
        }
    }
    $subprojects = @($subprojects | Sort-Object -Unique)

    $priorityFiles = @()
    foreach ($f in ($buildFiles + $scriptFiles + $cFiles + $hFiles + $readmes)) {
        if ($null -ne $f) {
            $rel = $f.FullName.Substring($root.Path.Length + 1).Replace('\', '/')
            if ($priorityFiles -notcontains $rel) {
                $priorityFiles += $rel
            }
        }
    }
    $priorityFiles = @($priorityFiles | Select-Object -First 14)

    $docScore = if ($mdFiles.Count -ge 15) { 5 } elseif ($mdFiles.Count -ge 8) { 4 } elseif ($mdFiles.Count -ge 3) { 3 } elseif ($mdFiles.Count -ge 1) { 2 } else { 1 }
    $codeScore = if ($loc -ge 900) { 5 } elseif ($loc -ge 500) { 4 } elseif ($loc -ge 150) { 3 } elseif ($loc -gt 0) { 2 } else { 1 }
    $automationScore = 1
    if ($buildFiles.Count -gt 0) { $automationScore += 2 }
    if ($scriptFiles.Count -gt 0) { $automationScore += 1 }
    if ($testFiles.Count -gt 0) { $automationScore += 1 }
    if ($automationScore -gt 5) { $automationScore = 5 }

    $portabilityScore = if ($name -in @("cross-compilation", "screenshot-project", "system")) { 5 } elseif ($name -in @("networking", "filesystem", "network")) { 4 } elseif ($cFiles.Count -gt 0) { 3 } else { 2 }

    $maturityScore = [Math]::Round((($docScore + $codeScore + $automationScore + $portabilityScore) / 4.0), 2)
    $maturityLabel = Get-MaturityLabel $maturityScore

    $dynamicRisks = @()
    if ($cFiles.Count -eq 0) {
        $dynamicRisks += "Nao ha arquivos .c no escopo deste modulo de topo; o valor esta concentrado em documentacao ou em referencias para outras pastas."
    }
    if ($cFiles.Count -gt 0 -and $buildFiles.Count -eq 0) {
        $dynamicRisks += "Nao foi detectado arquivo de build local (Makefile/CMake) apesar da presenca de codigo C."
    }
    if ($artifactFiles.Count -gt 0) {
        $dynamicRisks += "Existem artefatos compilados versionados ($($artifactFiles.Count)); recomendado limpar e reforcar .gitignore."
    }
    if ($testFiles.Count -eq 0 -and $cFiles.Count -gt 0) {
        $dynamicRisks += "Nao foram identificados testes explicitos por nome de arquivo no modulo."
    }
    if ($loc -ge 700 -and $testFiles.Count -eq 0) {
        $dynamicRisks += "Volume de codigo alto sem evidencias claras de testes aumenta risco de regressao."
    }
    if ($apiRiskTotal -gt 0) {
        $dynamicRisks += "Heuristica estatica detectou $apiRiskTotal chamada(s) para APIs potencialmente perigosas (gets/strcpy/strcat/sprintf/scanf/system)."
    }
    if ($riskyCallCounts["gets"] -gt 0) {
        $dynamicRisks += "Uso de gets() identificado; esta API e insegura e deve ser removida."
    }
    if ($allocationCount -gt 0 -and $releaseCount -eq 0) {
        $dynamicRisks += "Alocacoes dinamicas sem free detectado no mesmo escopo de modulo; revisar leaks e ownership."
    }
    if ($todoCount -gt 0) {
        $dynamicRisks += "Existem marcadores TODO/FIXME/HACK no codigo ($todoCount), sinalizando debt tecnico ativo."
    }

    $riskList = @(@($profile.BaseRisks) + @($dynamicRisks) | Select-Object -Unique)
    $recommendations = @($profile.Priorities)

    if ($cFiles.Count -gt 0 -and $buildFiles.Count -eq 0) {
        $recommendations += "Introduzir Makefile local para compilar e validar todos os exemplos do modulo em lote."
    }
    if ($artifactFiles.Count -gt 0) {
        $recommendations += "Remover binarios/objetos do versionamento e automatizar limpeza com alvo clean."
    }
    if ($testFiles.Count -eq 0 -and $cFiles.Count -gt 0) {
        $recommendations += "Criar smoke tests minimos por subpasta para garantir comportamento esperado em CI."
    }
    if ($readmes.Count -eq 0) {
        $recommendations += "Adicionar README principal com objetivo, prerequisitos e comando de execucao."
    }
    if ($riskyCallCounts["gets"] -gt 0 -or $riskyCallCounts["strcpy"] -gt 0 -or $riskyCallCounts["strcat"] -gt 0 -or $riskyCallCounts["sprintf"] -gt 0) {
        $recommendations += "Substituir APIs de string inseguras por alternativas com limite explicito (fgets, snprintf, strn* com validacao)."
    }
    if ($riskyCallCounts["system"] -gt 0) {
        $recommendations += "Encapsular chamadas system() com validacao de entrada e lista branca de comandos."
    }
    if ($allocationCount -gt 0 -and $releaseCount -lt $allocationCount) {
        $recommendations += "Mapear ownership de memoria em cada fluxo e adicionar testes para vazamento/double free/use-after-free."
    }
    if ($todoCount -gt 0) {
        $recommendations += "Priorizar backlog de TODO/FIXME por criticidade e remover comentarios de debt expirado."
    }

    $recommendations = @($recommendations | Select-Object -Unique)

    $relatedItems = @($profile.Related)

    $relatedText = if ($relatedItems.Count -gt 0) {
        ($relatedItems | ForEach-Object { "- " + $_ }) -join "`n"
    } else {
        "- Sem relacoes registradas no perfil."
    }

    $subprojectText = if ($subprojects.Count -gt 0) {
        ($subprojects | ForEach-Object { "- " + $_ }) -join "`n"
    } else {
        "- Nao foram detectadas subpastas com README neste modulo."
    }

    $keyFilesText = if ($priorityFiles.Count -gt 0) {
        ($priorityFiles | ForEach-Object { "- " + $_ }) -join "`n"
    } else {
        "- Nao foram detectados arquivos-chave no filtro atual."
    }

    $topSourceLines = @($topSourceItems | ForEach-Object { "{0} ({1} linhas)" -f $_.Path, $_.Lines })
    $topSourcesText = To-Bullets -items $topSourceLines -emptyMessage "Sem fontes C/H para rankear por LOC."

    $platformSignalsText = To-Bullets -items $platformSignals -emptyMessage "Sem sinais de plataforma detectados."

    $apiRiskLines = @()
    foreach ($apiName in $riskyCallCounts.Keys) {
        $apiRiskLines += "{0}: {1}" -f $apiName, $riskyCallCounts[$apiName]
    }
    $apiRiskText = To-Bullets -items $apiRiskLines -emptyMessage "Sem chamadas de API de risco detectadas."

    $evidenceItems = @()
    foreach ($apiName in $riskyCallCounts.Keys) {
        if ($riskyCallCounts[$apiName] -gt 0) {
            $paths = @($riskyEvidence[$apiName])
            if ($paths.Count -gt 0) {
                $evidenceItems += "{0}: {1}" -f $apiName, ($paths -join ", ")
            }
        }
    }
    $evidenceText = To-Bullets -items $evidenceItems -emptyMessage "Sem evidencias de API de risco para listar."

    $findingsText = To-Bullets -items $findings -emptyMessage "Sem achados automaticos registrados."

    $riskText = To-Bullets -items $riskList -emptyMessage "Sem riscos registrados."

    $recommendationText = To-Bullets -items $recommendations -emptyMessage "Sem recomendacoes registradas."

    $roadmap30 = @(
        "Consolidar escopo do modulo $name e validar comandos de compilacao/execucao mais importantes.",
        "Padronizar README(s) com prerequisitos, entrada, saida esperada e erros comuns.",
        "Criar checklist de qualidade minima para novos exemplos (warnings, retorno de erro, limpeza de recursos)."
    )

    $roadmap60 = @(
        "Introduzir automacao de build e smoke tests para os caminhos criticos do modulo.",
        "Adicionar casos de borda e cenarios de falha para as funcoes mais sensiveis.",
        "Ajustar naming, estrutura de pastas e links internos para reduzir duplicidade."
    )

    $roadmap90 = @(
        "Integrar modulo com pipeline CI global do repositorio.",
        "Publicar matriz de maturidade com metricas de cobertura de exemplos e testes.",
        "Planejar proxima evolucao funcional conectando $name aos modulos relacionados listados nesta analise."
    )

    $roadmap30Text = ($roadmap30 | ForEach-Object { "- " + $_ }) -join "`n"
    $roadmap60Text = ($roadmap60 | ForEach-Object { "- " + $_ }) -join "`n"
    $roadmap90Text = ($roadmap90 | ForEach-Object { "- " + $_ }) -join "`n"

    $reportPath = Join-Path $analysisDir ($name + ".analysis.md")

    $content = @"
# Analise Completa: $name

## 1. Escopo e papel no repositorio
$($profile.Scope)

## 2. Leitura tecnica do dominio
- Dominio principal: $($profile.Domain)
- Valor didatico: $($profile.Learning)
- Relacao com outros modulos:
$relatedText

## 3. Inventario tecnico objetivo
- Arquivos totais: $($files.Count)
- Codigo fonte C: $($cFiles.Count)
- Headers C: $($hFiles.Count)
- Arquivos Markdown: $($mdFiles.Count)
- READMEs identificados: $($readmes.Count)
- Arquivos de build: $($buildFiles.Count)
- Scripts auxiliares: $($scriptFiles.Count)
- Artefatos compilados versionados: $($artifactFiles.Count)
- LOC aproximado (.c + .h): $loc
- Testes detectados por nome: $($testFiles.Count)

## 4. Estrutura interna observada
$subprojectText

## 5. Arquivos-chave mapeados
$keyFilesText

## 6. Telemetria tecnica do codigo
- Funcoes detectadas (heuristica): $functionCount
- Ocorrencias de controle de fluxo (if/switch/for/while/do): $controlFlowCount
- Marcadores de debt (TODO/FIXME/HACK/XXX): $todoCount
- Chamadas de alocacao (malloc/calloc/realloc): $allocationCount
- Chamadas de liberacao (free): $releaseCount
- Total de chamadas em APIs de risco mapeadas: $apiRiskTotal

### 6.1 APIs de risco (contagem)
$apiRiskText

### 6.2 Sinais de portabilidade observados
$platformSignalsText

## 7. Fontes de maior volume (LOC)
$topSourcesText

## 8. Achados tecnicos prioritarios (auto-heuristica)
$findingsText

## 9. Evidencias de API de risco por arquivo
$evidenceText

## 10. Matriz de maturidade (0 a 5)
| Dimensao | Nota | Evidencia resumida |
|---|---:|---|
| Documentacao | $docScore | Quantidade de Markdown/README no escopo do modulo |
| Densidade de codigo | $codeScore | LOC e quantidade de fontes C/H observados |
| Automacao e teste | $automationScore | Presenca de build scripts, scripts utilitarios e testes nomeados |
| Portabilidade | $portabilityScore | Sinais de multiplataforma e acoplamento a APIs de SO |
| **Media geral** | **$maturityScore** | **Classificacao: $maturityLabel** |

## 11. Riscos, lacunas e debt tecnico
$riskText

## 12. Recomendacoes priorizadas
$recommendationText

## 13. Roadmap recomendado (30/60/90 dias)
### 30 dias
$roadmap30Text

### 60 dias
$roadmap60Text

### 90 dias
$roadmap90Text

## 14. Criterios de pronto para proxima fase
- Build reproduzivel por comando unico no escopo do modulo.
- Zero warning critico nas compilacoes principais com flags de qualidade.
- Documentacao com exemplos executaveis e saida esperada validada.
- Casos de erro principais cobertos por smoke tests ou testes unitarios.
- Nao existencia de artefatos binarios acidentais no controle de versao.

## 15. Observacao de metodo
Esta analise combina leitura de estrutura, metricas objetivas e heuristicas estaticas de codigo (regex), portanto nao substitui compilacao com warnings agressivos e execucao de testes.
"@

    Set-Content -Path $reportPath -Value $content -Encoding UTF8

    $indexRows += [PSCustomObject]@{
        Project = $name
        Total = $files.Count
        CodeFiles = ($cFiles.Count + $hFiles.Count)
        Md = $mdFiles.Count
        Loc = $loc
        Functions = $functionCount
        ApiRisk = $apiRiskTotal
        HighFindings = $highSeverityFindings
        Maturity = ("{0} ({1})" -f $maturityLabel, $maturityScore)
        ReportFile = ($name + ".analysis.md")
    }
}

$indexHeader = @"
# Analises Completas por Projeto

Este diretorio consolida uma analise detalhada para cada projeto de topo do repositorio C-Codebase.

## Metodologia utilizada
- Inventario automatico de arquivos por modulo.
- Leitura de READMEs representativos de cada dominio.
- Quantificacao de codigo (.c/.h), documentacao (.md), build e scripts.
- Telemetria estatica de codigo (heuristica): funcoes, controle de fluxo, APIs de risco e sinais de plataforma.
- Classificacao de maturidade por dimensoes (documentacao, codigo, automacao e portabilidade).
- Geracao de achados priorizados, recomendacoes e roadmap 30/60/90 por modulo.

## Cobertura de analise
| Projeto | Arquivos | C/H | MD | LOC | Funcoes | APIs risco | Achados altos | Maturidade | Relatorio |
|---|---:|---:|---:|---:|---:|---:|---:|---|---|
"@

$indexBody = ($indexRows | Sort-Object Project | ForEach-Object {
    "| {0} | {1} | {2} | {3} | {4} | {5} | {6} | {7} | {8} | [{0}]({9}) |" -f $_.Project, $_.Total, $_.CodeFiles, $_.Md, $_.Loc, $_.Functions, $_.ApiRisk, $_.HighFindings, $_.Maturity, $_.ReportFile
}) -join "`n"

$indexFooter = @"

## Leitura recomendada
1. Comecar por modules com maturidade Alta/Media-Alta para observar padroes consolidados.
2. Tratar primeiro riscos de seguranca e portabilidade (networking, system, cross-compilation).
3. Em seguida, reduzir debt de consistencia nos modulos documentais e de entrada (beginner, files, json, preprocessor).
4. Evoluir para uma trilha unica de build/teste em todo o repositorio.
"@

$indexContent = $indexHeader + "`n" + $indexBody + "`n" + $indexFooter
Set-Content -Path (Join-Path $analysisDir "INDEX.md") -Value $indexContent -Encoding UTF8

Write-Output "Analises geradas em: $analysisDir"
Write-Output "Quantidade de relatorios: $($indexRows.Count)"
