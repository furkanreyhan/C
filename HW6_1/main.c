#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CIRCUIT_FILENAME "circuit.txt"
#define INPUT_FILENAME "input.txt"
#define BUFFER_SIZE 255
#define NAME_LENGTH 100

// Component Types
#define INPUT 1
#define NOT_GATE 2
#define AND_GATE 3
#define OR_GATE 4
#define FLIPFLOP 5

typedef char label[NAME_LENGTH];

typedef struct _Component
{
    label name;
    int type;
    label in1_name;
    label in2_name;
    struct _Component *in1;
    struct _Component *in2;
    struct _Component *out;
    int value;
} Component;

typedef struct _Node
{
    Component *component;
    struct _Node *next;
} Node;

typedef struct
{
    Node *first;
    int size;
    Component *out;
} Circuit;

Component *new_component(label name, int type, char *in1_name, char *in2_name); // Create a new component
Component *find_component_by_name(label name, Circuit *circuit);                // Find a component in the circuit by name
void add_component_to_circuit(Component *component, Circuit *circuit);
void create_component_connections(Circuit *circuit); // Iterate over component list and create i/o connections
Component *find_circuit_out(Circuit *circuit);       // Find the circuit output component

void parse_input_components(char *line, FILE *fp, Circuit *circuit);
void parse_gate_components(char *line, FILE *fp, Circuit *circuit); // Parse gate components (NOT, AND, OR, FLIPFLOP)
void parse_and_set_input_values(Circuit *circuit, char *line);
char *readline(char *buffer, FILE *fp); // Read oneline from file without "\n" character

/* Gate simulators */
int and_gate(int i1, int i2);
int or_gate(int i1, int i2);
int not_gate(int i);
int flipflop(int i, int formerout);

int simulate(Circuit *circuit); // Simulate whole circuit
int eval(Component *component);

int type_str_to_int(char *typestr);

void free_circuit(Circuit *circuit);

int main()
{
    Circuit *circuit = (Circuit *)malloc(sizeof(Circuit));

    char line[BUFFER_SIZE];
    FILE *fp_circuit = fopen(CIRCUIT_FILENAME, "r");
    parse_input_components(line, fp_circuit, circuit);
    parse_gate_components(line, fp_circuit, circuit);
    create_component_connections(circuit);
    fclose(fp_circuit);

    FILE *fp_input = fopen(INPUT_FILENAME, "r");
    while (readline(line, fp_input) != NULL)
    {
        parse_and_set_input_values(circuit, line);
        int output = simulate(circuit);
        printf("%d\n", output);
    }

    fclose(fp_input);
    free_circuit(circuit);

    return 0;
}

Component *new_component(label name, int type, char *in1_name, char *in2_name)
{
    Component *c = (Component *)malloc(sizeof(Component));
    strcpy(c->name, name);
    c->type = type;
    strcpy(c->in1_name, in1_name);
    if (in2_name != NULL)
        strcpy(c->in2_name, in2_name);
    return c;
}

Component *find_component_by_name(label name, Circuit *circuit)
{
    Node *cursor = circuit->first;

    while (cursor != NULL)
    {
        if (strcmp(name, cursor->component->name) == 0)
            return cursor->component;

        cursor = cursor->next;
    }

    return NULL;
}

void add_component_to_circuit(Component *component, Circuit *circuit)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->component = component;
    node->next = NULL;

    // If list is empty, add first element
    if (circuit->first == NULL)
    {
        circuit->first = node;
        return;
    }

    Node *cursor = circuit->first;
    while (cursor != NULL)
    {
        if (cursor->next == NULL)
            break;
        cursor = cursor->next;
    }
    cursor->next = node;
}

void create_component_connections(Circuit *circuit)
{
    Node *current = circuit->first;
    while (current != NULL)
    {
        Component *in1 = find_component_by_name(current->component->in1_name, circuit);
        Component *in2 = find_component_by_name(current->component->in2_name, circuit);

        if (in1 != NULL)
        {
            current->component->in1 = in1;
            in1->out = current->component;
        }

        if (in2 != NULL)
        {
            current->component->in2 = in2;
            in2->out = current->component;
        }
        current = current->next;
    }
}

Component *find_circuit_out(Circuit *circuit)
{
    Component *circuit_output = circuit->first->component;

    Node *current = circuit->first;
    while (current != NULL)
    {
        if (current->component->out == NULL)
        {
            return current->component;
        }
        current = current->next;
    }
    return NULL;
}

int simulate(Circuit *circuit)
{
    // Set the circuit output element if not identified
    if (circuit->out == NULL)
        circuit->out = find_circuit_out(circuit);

    return eval(circuit->out);
}

int eval(Component *component)
{
    switch (component->type)
    {
    case INPUT:
        return component->value;
    case NOT_GATE:
        return not_gate(eval(component->in1));
    case AND_GATE:
        return and_gate(eval(component->in1), eval(component->in2));
    case OR_GATE:
        return or_gate(eval(component->in1), eval(component->in2));
    case FLIPFLOP:
    {
        component->value = flipflop(eval(component->in1), component->value);
        return component->value;
    }
    }
}
int flipflop(int i, int formerout)
{
    if (i == formerout)
        return 0;
    return 1;
}

/* GATES */
int not_gate(int i)
{
    return i == 0 ? 1 : 0;
}

int and_gate(int i1, int i2)
{
    if ((i1 == i2) && (i1 != 0))
        return 1;

    return 0;
}

int or_gate(int i1, int i2)
{
    if (i1 == 0 && i2 == 0)
        return 0;
    return 1;
}

int type_str_to_int(char *str)
{

    if (strcmp(str, "INPUT") == 0)
        return INPUT;
    if (strcmp(str, "NOT") == 0)
        return NOT_GATE;
    if (strcmp(str, "AND") == 0)
        return AND_GATE;
    if (strcmp(str, "OR") == 0)
        return OR_GATE;
    if (strcmp(str, "FLIPFLOP") == 0)
        return FLIPFLOP;

    return -1;
}

void parse_input_components(char *line, FILE *fp, Circuit *circuit)
{
    readline(line, fp);

    char *token = strtok(line, " ");
    token = strtok(NULL, " ");
    while (token != NULL)
    {
        Component *input = new_component(token, INPUT, "", "");
        add_component_to_circuit(input, circuit);
        token = strtok(NULL, " ");
    }
}

void parse_gate_components(char *line, FILE *fp, Circuit *circuit)
{
    while (readline(line, fp) != NULL)
    {
        char *type = strtok(line, " ");
        char *name = strtok(NULL, " ");
        char *in1_name = strtok(NULL, " ");
        char *in2_name = strtok(NULL, " ");

        int type_int = type_str_to_int(type);

        Component *component = new_component(name, type_int, in1_name, in2_name);

        add_component_to_circuit(component, circuit);
    }
}

void parse_and_set_input_values(Circuit *circuit, char *line)
{
    Node *current = circuit->first;
    char *token = strtok(line, " ");
    while (token != NULL)
    {
        current->component->value = atoi(token);
        current = current->next;
        token = strtok(NULL, " ");
    }
};

char *readline(char *buffer, FILE *fp)
{
    char *line = fgets(buffer, BUFFER_SIZE, fp);
    size_t len = strlen(buffer);
    if (buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    return line;
}

void free_circuit(Circuit *circuit)
{
    Node *current = circuit->first;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp->component);
        free(temp);
    }
}