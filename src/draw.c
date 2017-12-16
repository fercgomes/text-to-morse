/* Desenha uma ilustracao da arvore em um arquivo */
void tree_draw(tNode *a , int nivel, FILE* fp){
    int x;
    if (a !=NULL)  {
        for(x=1; x<=nivel; x++)
            fprintf(fp, "=");

    fprintf(fp, "(%2d)\n", a->ascii);
    if (a->left != NULL) tree_draw(a->left, (nivel+1), fp);
    if (a->right != NULL) tree_draw(a->right, (nivel+1), fp);
    }
}

/* Salva em um arquivo txt o estado da arvore */ 
void save_tree_state(tNode* root, int ascii, const char* morse, int operation){
	/* 0 - Insertion, 1 - Splay */
    FILE* db_file = fopen("debug.txt", "a");
    if(operation == 0) fprintf(db_file, "Inserindo ASCII %d com Morse %s.\n", ascii, morse);
	else fprintf(db_file, "Fazendo Splay no nodo ASCII %d.\n", ascii);	
    fprintf(db_file, "========================================================================================\n");
    tree_draw(root, 1, db_file);
    fprintf(db_file, "\n");
    fclose(db_file);
}
