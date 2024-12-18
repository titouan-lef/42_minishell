#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
	TOKEN_PIPE,
	TOKEN_P_OPEN,
	TOKEN_P_CLOSE,
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_UNKNOWN
} Token;

const char* getTokenName(Token token) {
	switch (token) {
		case TOKEN_PIPE:    return "PIPE";
		case TOKEN_P_OPEN:  return "P_OPEN";
		case TOKEN_P_CLOSE: return "P_CLOSE";
		case TOKEN_WORD:    return "WORD";
		case TOKEN_REDIR:   return "REDIR";
		case TOKEN_AND:     return "AND";
		case TOKEN_OR:      return "OR";
		default:            return "UNKNOWN";
	}
}

void skipSpaces(const char *input, int *index) {
	while (isspace(input[*index])) {
		(*index)++;
	}
}

void getWord(const char *input, int *index, char *buffer) {
	int start = *index;
	while (input[*index] && input[*index] != '|' && input[*index] != '(' && input[*index] != ')' && input[*index] != '&' && input[*index] != '<' && input[*index] != '>' && input[*index] != ' ') {
		(*index)++;
	}
	strncpy(buffer, input + start, *index - start);
	buffer[*index - start] = '\0';
}

Token getToken(const char *input, int *index, char *outputBuffer) {
	char current = input[*index];
	char wordBuffer[256] = {0};

	skipSpaces(input, index);
	current = input[*index];

	if (current == '|') {
		(*index)++;
		if (input[*index] == '|') { (*index)++; return TOKEN_OR; }
		return TOKEN_PIPE;
	}
	if (current == '(') { (*index)++; return TOKEN_P_OPEN; }
	if (current == ')') { (*index)++; return TOKEN_P_CLOSE; }
	if (current == '<' || current == '>') {
		char redir = current;
		(*index)++;
		skipSpaces(input, index);
		getWord(input, index, wordBuffer);
		sprintf(outputBuffer, "%c%s", redir, wordBuffer);
		return TOKEN_REDIR;
	}
	if (current == '&') {
		(*index)++;
		if (input[*index] == '&') { (*index)++; return TOKEN_AND; }
	}

	if (isalnum(current) || current == '_' || current == '\'' || current == '"') {
		getWord(input, index, wordBuffer);
		strcpy(outputBuffer, wordBuffer);
		return TOKEN_WORD;
	}

	(*index)++;
	return TOKEN_UNKNOWN;
}

void runAutomate(const char *input) {
	int index = 0;
	Token token;
	char buffer[256];

	printf("Entrée : %s\n", input);
	printf("Tokens détectés :\n");

	while (input[index] != '\0') {
		memset(buffer, 0, sizeof(buffer));
		token = getToken(input, &index, buffer);

		if (token != TOKEN_UNKNOWN) {
			printf(" - %s", getTokenName(token));
			if (strlen(buffer) > 0) {
				printf(" : %s", buffer);
			}
			printf("\n");
		}
	}

	printf("Fin de l'analyse.\n");
}

int main() {
	const char *inputs[] = {
		"echo hello > file",
		"(ls -l) | grep test",
		"cat < input.txt && echo done",
		"echo 'hello world' || echo 'error'",
		"command && (nested command)",
		"'cat' < in > out && echo Bpn'jour'"
	};

	int numInputs = sizeof(inputs) / sizeof(inputs[0]);
	for (int i = 0; i < numInputs; i++) {
		printf("\nTest %d :\n", i + 1);
		runAutomate(inputs[i]);
	}

	return 0;
}
