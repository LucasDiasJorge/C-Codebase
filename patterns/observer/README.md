# 🎯 Observer Pattern em C

## 📖 Conceito

O padrão Observer é um padrão de design comportamental que define uma dependência um-para-muitos entre objetos. Quando um objeto (Subject) muda de estado, todos os seus dependentes (Observers) são notificados automaticamente.

## 🧠 Por que usar o Observer Pattern?

- **Desacoplamento**: O Subject não precisa conhecer os Observers específicos
- **Extensibilidade**: Novos observers podem ser adicionados facilmente
- **Notificação automática**: Mudanças são propagadas automaticamente
- **Flexibilidade**: Observers podem ser registrados/removidos dinamicamente

## 🏗️ Implementação em C

### Estruturas Principais

```c
// Tipo de função callback para observers
typedef void (*ObserverCallback)(int);

// Estrutura do Subject (observado)
typedef struct {
    int value;                              // Valor sendo observado
    ObserverCallback observers[MAX_OBSERVERS]; // Array de observers
    int observer_count;                     // Contador de observers
} Subject;
```

### Funções Principais

1. **`register_observer()`**: Registra um novo observer
2. **`notify_observers()`**: Notifica todos os observers
3. **`set_value()`**: Altera o valor e notifica observers

## 🎯 Como Funciona

### 1. Registro de Observer
```c
void register_observer(Subject *subject, ObserverCallback observer) {
    if (subject->observer_count < MAX_OBSERVERS) {
        subject->observers[subject->observer_count++] = observer;
    }
}
```

### 2. Notificação dos Observers
```c
void notify_observers(Subject *subject) {
    for (int i = 0; i < subject->observer_count; i++) {
        subject->observers[i](subject->value);
    }
}
```

### 3. Mudança de Estado
```c
void set_value(Subject *subject, int new_value) {
    subject->value = new_value;
    notify_observers(subject);  // Notifica automaticamente
}
```

## 🔄 Fluxo de Execução

1. **Inicialização**: Subject é criado
2. **Registro**: Observers são registrados
3. **Mudança**: Valor do subject muda
4. **Notificação**: Todos observers são chamados automaticamente

## 💻 Exemplo de Uso

```c
// Definir observers
void observer1(int new_value) {
    printf("Observer 1: Valor mudou para %d\n", new_value);
}

void observer2(int new_value) {
    printf("Observer 2: Valor mudou para %d\n", new_value);
}

int main() {
    Subject subject = {0, {NULL}, 0};
    
    // Registrar observers
    register_observer(&subject, observer1);
    register_observer(&subject, observer2);
    
    // Mudar valor (notifica automaticamente)
    set_value(&subject, 42);   // Ambos observers são chamados
    set_value(&subject, 100);  // Ambos observers são chamados novamente
    
    return 0;
}
```

## 📊 Saída Esperada

```
Observer 1: Value changed to 42
Observer 2: Value changed to 42
Observer 1: Value changed to 100
Observer 2: Value changed to 100
```

## 🛠️ Compilação e Execução

```bash
# Compilar
gcc -o observer main.c

# Executar
./observer
```

## 🎯 Aplicações Práticas

- **GUI**: Atualização de interface quando dados mudam
- **Sistemas de Cache**: Invalidação automática de cache
- **Logging**: Log automático de mudanças de estado
- **Sistemas de Notificação**: Envio de notificações para usuários

## 🔍 Variações e Melhorias

### 1. Observer com Dados Específicos
```c
typedef struct {
    void (*callback)(void* data);
    void* user_data;
} Observer;
```

### 2. Remoção de Observers
```c
void unregister_observer(Subject *subject, ObserverCallback observer);
```

### 3. Filtragem de Eventos
```c
typedef enum { CHANGE_TYPE_VALUE, CHANGE_TYPE_STATE } ChangeType;
void notify_observers_filtered(Subject *subject, ChangeType type);
```

## ⚡ Vantagens e Desvantagens

### ✅ Vantagens
- Baixo acoplamento entre Subject e Observers
- Suporte dinâmico para adicionar/remover observers
- Princípio Aberto/Fechado (Open/Closed Principle)

### ❌ Desvantagens
- Overhead de memória para manter lista de observers
- Ordem de notificação pode ser importante
- Debugging mais complexo (chamadas indiretas)

## 🎓 Conceitos C Demonstrados

- **Function Pointers**: Callbacks para observers
- **Structs**: Organização de dados
- **Arrays**: Armazenamento de observers
- **Modularidade**: Separação de responsabilidades

Este exemplo demonstra como implementar padrões de design orientados a objeto em C, uma linguagem procedural, usando ponteiros para funções e estruturas bem organizadas.
