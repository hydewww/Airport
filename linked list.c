#include <stdio.h>
typedef struct anode {
	int num;
	struct anode* next;
};
typedef struct anode* node;
node createnode();
int getmax(node head);
int getmin(node head);
int getsum(node head);
void freelink(node head);
node differenceSet(node a, node b);
node intersectionSet(node a, node b);
void printlink(node head);
void swap(node head,int s1, int t1, int s2, int t2);

main() {
	printf("Please input a list (end by -1): ");
	node a=createnode();
	printf("Please input four integers: ");
	int s1, t1, s2, t2;
	scanf("%d %d %d %d", &s1, &t1, &s2, &t2);
	//input
	swap(a,s1, t1, s2, t2);
	//swap
	printf("The new list is:");
	printlink(a);
	//print
	freelink(a);
	//free
	return 0;
}

node createnode() {
	node head = (node)malloc(sizeof(struct anode));
	head->next = NULL;
	node last = head;
	int in;
	while (scanf("%d", &in) && in != -1) {
		node p = (node)malloc(sizeof(struct anode));
		p->num = in;
		p->next = NULL;
		last->next = p;
		last = p;
	}
	return head;
}
int getmax(node head) {
	int max = -1;
	node p = head->next;
	while (p) {
		if (p->num > max) {
			max = p->num;
		}
		p = p->next;
	}
	return max;
}
int getmin(node head) {
	int min = 999999999;
	node p = head->next;
	while (p) {
		if (p->num < min) {
			min = p->num;
		}
		p = p->next;
	}
	return min;
}
int getsum(node head) {
	int sum = 0;
	node p = head->next;
	while (p) {
		sum += p->num;
		p = p->next;
	}
	return sum;
}
node differenceSet(node a, node b) {
	node a1 = a->next; node b1 = b->next;
	node head = (node)malloc(sizeof(struct anode)); head->next = NULL;
	node last = head;
	while (a1&&b1) {
		if (a1->num > b1->num) {
			b1 = b1->next;
		}
		else if (a1->num == b1->num) {
			a1 = a1->next; b1 = b1->next;
		}
		else {
			node p = (node)malloc(sizeof(struct anode));p->next = NULL;
			p->num = a1->num;
			last->next = p;
			last = p;
			a1 = a1->next;
		}
	}
	while (a1) {
		node p = (node)malloc(sizeof(struct anode)); p->next = NULL;
		p->num = a1->num;
		last->next = p;
		last = p;
		a1 = a1->next;
	}
	return head;
}
node intersectionSet(node a, node b) {
	node a1 = a->next; node b1 = b->next;
	node head = (node)malloc(sizeof(struct anode)); head->next = NULL;
	node last = head;
	while (a1&&b1) {
		if (a1->num > b1->num) {
			b1 = b1->next;
		}
		else if (a1->num == b1->num) {
			node p = (node)malloc(sizeof(struct anode)); p->next = NULL;
			p->num = a1->num;
			last->next = p;
			last = p;
			a1 = a1->next; b1 = b1->next;
		}
		else {
			a1 = a1->next;
		}
	}
	return head;
}
void printlink(node head) {
	node p = head->next;
	printf("%d", p->num);
	while (p=p->next) {
		printf(" %d", p->num);
	}
	printf("\n");
}
void freelink(node head) {
	node p= head;
	while (p) {
		node now = p;
		p = p->next;
		free(now);
	}
}
void swap(node head,int s1, int t1, int s2, int t2) {
	node p = head;
	int i = 0;
	node S1f, T1, S2f, T2,tmp;
	while (p) {
		if (i == s1 - 1) {
			S1f = p;
		}
		else if (i == t1) {
			T1 = p;
		}
		else if (i == s2 - 1) {
			S2f = p;
		}
		else if (i == t2) {
			T2 = p;
			break;
		}
		p = p->next;
		i++;
	}
	tmp = S1f->next;
	S1f->next = S2f->next;
	S2f->next = tmp;
	tmp = T1->next;
	T1->next = T2->next;
	T2->next = tmp;
}