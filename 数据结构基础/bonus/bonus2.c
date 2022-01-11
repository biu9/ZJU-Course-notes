#include<stdio.h>

int main(){
    int num;
    scanf("%d",&num);
    int hats[1000];
    int people[1000];
    int hats_order[1000];
    int people_order[1000];

    for(int i=0;i<num;i++)
        scanf("%d",&hats[i]);
    for(int i=0;i<num;i++)
        scanf("%d",&people[i]);

    int order_hats = 0;
    int order_people = 0;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(i != j){
                if(hats[i] > hats[j]){
                    order_hats++;
                }
                if(people[i] > people[j]){
                    order_people++;
                }
            }
        }
        hats_order[i] = order_hats;
        people_order[i] = order_people;
        order_hats = 0;
        order_people = 0;
    }

    for(int i=num-1;i>=0;i--){
        for(int j = 0;j<num;j++){
            if(people_order[j] == hats_order[i]){
                if(i == 0)
                    printf("%d",j+1);
                else
                    printf("%d ",j+1);
            }

        }
    }
}