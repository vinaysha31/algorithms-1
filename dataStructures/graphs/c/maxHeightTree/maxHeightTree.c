#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node_t_ {
	int degree;
	bool candidate;
} node_t;

int* findMinHeightTrees(int n, int** edges, int edgesRowSize, int edgesColSize, int* returnSize) {

	int i, j, *ans, numCands, *edge;
	node_t *cands; 
	int iter=0;

	cands = (node_t *) malloc( n *sizeof(node_t) );
	memset(cands, 0, n *sizeof(node_t) );
	ans = (int *) malloc(2 *sizeof(int));
	printf("ans is at %p\n", ans);
	for (i=0; i<n; i++) {
		cands[i].candidate = true;
	}

	do {	
		printf("Iteration ... %d\n", iter++);
		for (i=0; i<edgesRowSize; i++) {
			edge = *(edges + i);
			if ( cands[edge[0]].candidate  && 
				 cands[edge[1]].candidate )  {
					cands[edge[0]].degree++;
					cands[edge[1]].degree++;
			}
		}
		numCands = 0;
		for (i=0; i<n; i++) {
			if ( cands[i].degree <= 1 ) {
				cands[i].candidate = false;
			} else {
				numCands++;
			}
			cands[i].degree = 0;
		}
	} while (numCands > 2);

	*returnSize = numCands;
	j=0;
	for (i=0; i<n; i++) {
		if (cands[i].candidate == true) {
			printf("Candidate %d\n", i);
			*(ans+j) = i;
			j++;
		}
	}
	free(cands);
	*(ans) = numCands;
	return ans;
    
}

int main() {
	int **edges; // { { 1, 0 }, { 1, 2 }, {1, 3} };
	int ansSize, *ans, i;

	edges = (int **) malloc ( 3 * sizeof(int *) );
	for (i=0; i<3; i++) {
		edges[i] = (int *) malloc( 2 * sizeof(int) );
	}
	edges[0][0] = 1;
	edges[0][1] = 0;
	edges[1][0] = 1;
	edges[1][1] = 2;
	edges[2][0] = 1;
	edges[2][1] = 3;
	ans = findMinHeightTrees( 4, edges, 3, 2, &ansSize);
	for (i=0; i<ansSize; i++) {
		printf("Ans %d\n", *(ans+i));
	}
	for (i=0; i<3; i++) {
		free(edges[i]);
	}
	free(edges); free(ans);

	edges = (int **) malloc ( 5 * sizeof(int *) );
	for (i=0; i<5; i++) {
		edges[i] = (int *) malloc( 2 * sizeof(int) );
	}
	edges[0][0] = 0;
	edges[0][1] = 3;
	edges[1][0] = 1;
	edges[1][1] = 3;
	edges[2][0] = 2;
	edges[2][1] = 3;
	edges[3][0] = 4;
	edges[3][1] = 3;
	edges[4][0] = 5;
	edges[4][1] = 4;
	ans = findMinHeightTrees( 6, edges, 5, 2, &ansSize);
	for (i=0; i<ansSize; i++) {
		printf("Ans %d\n", *(ans+i));
	}
	for (i=0; i<5; i++) {
		free(edges[i]);
	}
	free(edges); 
	printf("Free ans %p\n", ans);
	free(ans);

	printf("Testcase 3 \n");
	edges = (int **) malloc ( 5 * sizeof(int *) );
	assert(edges);
	printf("edges allocation complete\n");
	for (i=0; i<5; i++) {
		edges[i] = (int *) malloc( 2 * sizeof(int) );
		assert(edges[i]);
	}
	printf("allocation complete\n");
	fflush(stdout);
	edges[0][0] = 3;
	edges[0][1] = 0;
	edges[1][0] = 3;
	edges[1][1] = 1;
	edges[2][0] = 3;
	edges[2][1] = 2;
	edges[3][0] = 3;
	edges[3][1] = 4;
	edges[4][0] = 5;
	edges[4][1] = 4;
	printf("Call to findMinHeightTrees\n");
	ans = findMinHeightTrees( 6, edges, 5, 2, &ansSize);
	for (i=0; i<ansSize; i++) {
		printf("Ans %d\n", *(ans+i));
	}
	for (i=0; i<5; i++) {
		free(edges[i]);
	}
	free(edges); free(ans);
}
