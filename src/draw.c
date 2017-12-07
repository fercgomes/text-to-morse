#define I_MAX 64
#define J_MAX 2048
#define COMPACT

int _print_t(tNode *tree, int is_left, int offset, int depth, char s[I_MAX][J_MAX])
{
    char b[I_MAX];
    int width = 5;
    int left, right, i;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->ascii);

    left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(tNode *tree, const char* filename, int ascii, const char* morse)
{
	FILE* db_file;
	char s[I_MAX][J_MAX];
	int i;
	for (i = 0; i < I_MAX; i++)
		sprintf(s[i], "%80s", "=");

	_print_t(tree, 0, 0, 0, s);
	db_file = fopen(filename, "a");
	
	fprintf(db_file, "Inserindo ASCII: %d | Morse: %s\n", ascii, morse);
	fprintf(db_file, "===================================================================================================================================================================================\n");
	for (i = 0; i < I_MAX; i++)
		fprintf(db_file, "%s\n", s[i]);

	fclose(db_file);
}

void Desenha(tNode *a , int nivel, FILE* fp){
    int x;
    if (a !=NULL)  {
        for(x=1; x<=nivel; x++)
            fprintf(fp, "=");

    fprintf(fp, "(%2d)\n", a->ascii);
    if (a->left != NULL) Desenha(a->left, (nivel+1), fp);
    if (a->right != NULL) Desenha(a->right, (nivel+1), fp);
    }
}

void save_tree_state(tNode* root, int ascii, const char* morse){
	print_t(root, "debug.txt", ascii, morse);
}

void save_tree_state_2(tNode* root, int ascii, const char* morse){
    FILE* db_file = fopen("debug.txt", "a");
    fprintf(db_file, "Inserindo ASCII %d com Morse %s.\n", ascii, morse);
    fprintf(db_file, "========================================================================================\n");
    Desenha(root, 1, db_file);
    fprintf(db_file, "\n");
    fclose(db_file);
}
