#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int *value;
    int size_tree;
    int degree2_size_list;
} Tree;
 
Tree tree;
 
typedef struct {
    int value;
    int index;
} Pair;
Pair *m_with_index, *p_with_index;;
 
int *t, *position_p, *answer;
 
int closet_power2_n(int n) {
    int degree2 = 1;
    while(degree2 < n)
        degree2 = degree2 << 1;
    return degree2;
}
 
void build_tree(Tree *tree, int size) {
    tree->degree2_size_list = closet_power2_n(size);
    tree->size_tree = 2 * closet_power2_n(size);
    tree->value = (int *) calloc(tree->size_tree, sizeof(int));
    /*
    for (int i = 0; i < size; i++) {
        tree->value[tree->degree2_size_list - 1 + i] = a[i].value;
    }
    for (int i = tree->degree2_size_list - 2; i >= 0; i--) {
        tree->value[i] = __max(tree->value[2 * i + 1], tree->value[2 * i + 2]);
    }
     */
}
 
void update_element(Tree *tree, int new_value, int i) {
    i += tree->degree2_size_list - 1;
    tree->value[i] = new_value;
    while (i > 0) {
        i = (i - 1) / 2;
        tree->value[i] = __max(tree->value[2 * i + 1], tree->value[2 * i + 2]);
    }
}
 
int query_tree(Tree *tree, int l, int r) {
    if (l > r)
        return 0;
    l += tree->degree2_size_list - 1;
    r += tree->degree2_size_list - 1;
    int ans = 0;
    while (l < r) {
        if (!(l & 1))
            ans = __max(ans, tree->value[l]); // l - Р С—РЎР‚Р В°Р Р†РЎвЂ№Р в„– РЎР‚Р С•Р Т‘Р С‘РЎвЂљР ВµР В»РЎРЉ - РЎвЂЎР ВµРЎвЂљР Р…РЎвЂ№Р в„–
        if (r & 1)
            ans = __max(tree->value[r], ans); // r - Р В»Р ВµР Р†РЎвЂ№Р в„– РЎР‚Р С•Р Т‘Р С‘РЎвЂљР ВµР В»РЎРЉ - Р Р…Р ВµРЎвЂЎР ВµРЎвЂљР Р…РЎвЂ№Р в„–
        l = l / 2;
        r = (r - 1) / 2;
    }
    if (l == r)
        ans = __max(ans, tree->value[l]);
    return  ans;
}
 
int compare_pair (const void * a, const void * b) {
    if ( ((Pair *)a)->value > ((Pair *)b)->value )
        return 1;
    else if (((Pair *)a)->value < ((Pair*)b)->value)
        return -1;
    else {
        if (((Pair *)a)->index > ((Pair *)b)->index)
            return 1;
        else
            return -1;
    }
}
 
int compare_answer (const void * a, const void * b) {
    if ( *((int *)a) > *((int *)b) )
        return 1;
    else
        return -1;
}
 
int main() {
    FILE *in = fopen("input.txt", "r"), *out =  fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
 
    t = (int *) malloc(n * sizeof(int)); position_p = (int *) malloc(n * sizeof(int));
    m_with_index = (Pair *) malloc(n * sizeof(Pair)); p_with_index = (Pair *) malloc(n * sizeof(Pair)); answer = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d%d%d", &m_with_index[i].value, &p_with_index[i].value, &t[i]);
        m_with_index[i].index = i;
        p_with_index[i].index = i;
    }
 
    qsort(m_with_index, n, sizeof(Pair), compare_pair);
    qsort(p_with_index, n, sizeof(Pair), compare_pair);
 
    build_tree(&tree, n);
 
    for (int i = n - 1; i >= 0; i--) {
        position_p[p_with_index[i].index] = i;
    }
 
 
    int j = n - 1;
    int size_answer = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 1 && m_with_index[i].value != m_with_index[j].value
            && m_with_index[i].value != m_with_index[i + 1].value) {
            for (int k = j; k > i; k--) {
                update_element(&tree, t[m_with_index[k].index], position_p[m_with_index[k].index]);
            }
            j = i + 1;
        }
        int k = position_p[m_with_index[i].index];
        int position_p_more;
        for (position_p_more = k + 1; position_p_more < n && p_with_index[k].value == p_with_index[position_p_more].value; position_p_more++) {
        }
        int max_t = query_tree(&tree, position_p_more, n - 1);
        if (max_t <= t[m_with_index[i].index]) {
            answer[size_answer] = m_with_index[i].index + 1;
            size_answer++;
        }
    }
 
    qsort(answer, size_answer, sizeof(int), compare_answer);
 
    for (int i = 0; i < size_answer; i++) {
        fprintf(out, "%d ", answer[i]);
    }
 
    free(answer); free(p_with_index); free(position_p); free(tree.value); free(m_with_index); free(t); fclose(in); fclose(out);
    return 0;
}
