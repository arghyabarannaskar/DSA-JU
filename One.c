#include<stdio.h>
#include<stdlib.h>

struct List{
    int *arr;
    int size, capacity;
};

typedef struct List List;

void create(List *list, int capacity){
    list->arr = (int *)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
}

void insert(List *list, int data){
    if(list->size == list->capacity){
        int *new_arr = (int *)malloc(list->capacity * 2 * sizeof(int));
        for (int i = 0; i < list->size; i++)
            new_arr[i] = list->arr[i];
        free(list->arr);
        list->arr = new_arr;
        list->capacity = 2 * list->capacity;
    }
    list->arr[list->size++] = data;
}

void resize(List *list, int new_capacity){
    if(new_capacity < list->size){
        printf("\nAllocation may cause data loss. Aborting operation...");
        return;
    }

    int *new_arr = (int *)malloc(new_capacity * sizeof(int));

    for (int i = 0; i < list->size; i++)
        new_arr[i] = list->arr[i];

    free(list->arr);
    list->arr = new_arr;
    list->capacity = new_capacity;
}

void display(List *list){
    if(list->size == 0){
        printf("List is empty. No elements to show....");
        return;
    }

    printf("\n");
    for (int i = 0; i < list->size; i++)
        printf("%d ", list->arr[i]);
    printf("\n");
}

void destroy(List *list){
    free(list->arr);
    list->capacity = list->size = 0;
}

void count(List *list){
    printf("\nThere are a total of %d elements in the list.", list->size);
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(List *list){
    int n = list->size;
    for (int i = 0; i < n / 2; i++){
        swap(&(list->arr[i]), &(list->arr[n - 1 - i]));
    }
}

void index_of(List *list, int target){
    int count = 0;
    printf("\nThe element is present in the following indices...\n");
    for (int i = 0; i < list->size; i++){
        if(list->arr[i] == target){
            count++;
            printf("%d ", i);
        }
    }

    if(count == 0)
        printf("Element does not exist in the list...");
}

void indexed_element(List *list, int index){
    if(index < 0 || index >= list->size){
        printf("Index is out of bounds...");
        return;
    }

    printf("Element at index %d is %d.", index, list->arr[index]);
}

void delete_value(List *list, int value) {
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (list->arr[i] == value) {
            found = 1;
            for (int j = i; j < list->size - 1; j++) {
                list->arr[j] = list->arr[j + 1];
            }
            list->size--;
            i--;
        }
    }
    if (!found) {
        printf("Value not found in the list\n");
    }
}

void mergeLists(List *list1, List *list2){
    for (int i = 0; i < list2->size; i++){
        insert(list1, list2->arr[i]);
    }
}

void split(List *list1, List *list2, int index){
    if(index < 0 || index >= list1->size){
        printf("Array index out of bounds. Aborting operation...");
        return;
    }

    for (int i = index; i < list1->size; i++){
        insert(list2, list1->arr[i]);
    }

    list1->size = index;
}

void merge(int arr[], int low, int mid, int high){
    int size = high - low + 1;
    int *a = (int *)malloc(size * sizeof(int));
    int left = low, right = mid + 1, idx = 0;
     printf("merging");
    while(left <= mid && right <= high){
        if(arr[left] < arr[right])
            a[idx++] = arr[left++];
        else
            a[idx++] = arr[right++];
    }

    while(left<=mid)
        a[idx++] = arr[left++];
    
    while(right <= high)
        a[idx++] = arr[right++];

    idx = 0;
    for (int index = low; index <= high; index++)
        arr[index] = a[idx++];

    free(a);
}

void mergeSort(int arr[], int low, int high){
    printf("Here");
    if(low < high){
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void sort(List *list){
    mergeSort(list->arr, 0, list->size - 1);
}

int main(){
    List list;
    create(&list, 10);
    insert(&list, 2);
    insert(&list, 7);
    insert(&list, 4);
    insert(&list, 10);
    insert(&list, 4);
    display(&list);
    index_of(&list, 4);
    reverse(&list);
    display(&list);
    sort(&list);
    display(&list);
    destroy(&list);

    return 0;
}