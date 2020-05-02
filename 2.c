#include <stdio.h>
int main(){
	int t,c;
	scanf("%d",&t);
	for(int y=1;y<=t;y++){
	    int n,q;
	    char s[10000];
	    scanf("%d%d",&n,&q);
	    scanf("%s",&s);
	    for(int w=1;w<=q;w++){
	        int arr[26]={0};
	        scanf("%d",&c);
	        int count=0;
	        for(int i=0;i<n;i++){
	            arr[s[i]-'a']++;
	            if(arr[s[i]-'a']>c)count++;
	        }
	        printf("%d\n",count);
	    }
	}
	return 0;
}
