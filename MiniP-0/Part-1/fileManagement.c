#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {

      int cr = creat("newfile.txt",0644);

      if(cr==-1) {printf("Error in creating file. \n"); return 1; } ;


   
    while (1) {


       printf("Enter a command: "); 

    
    char a[40]; char b;
    scanf("%s",a);
    scanf("%c",&b);

    if( (strcmp("STOP",a)!=0) && (strcmp("PRINT",a)!=0) && (strcmp("INPUT",a)!=0 ) ) printf("Wrong command \n");
    

    else if(strcmp("STOP",a)==0) return 1;

    else if(strcmp("INPUT",a)==0) {


        int o = dup(1);
        

        int it = open("newfile.txt", O_WRONLY | O_APPEND);
        if(it==-1) {printf("Unable To Open. \n"); return 1;};

        dup2(it, 1);
        close(it);
       

        char t[4099];

        scanf("%[^\n]s",t);
        

         close(it);


       printf("%s\n",t);

       dup2(o, 1);

       close(o);
    

    }

    else if (strcmp("PRINT",a)==0) {

        
        
         int o = dup(0);

        int it = open("newfile.txt", O_RDONLY);
        if(it==-1) {printf("Unable To Open. \n"); return 1;};
        
        
         dup2(it,0);

         close(it);

        char p;
         int pp =scanf("%c",&p); 
         
        
          while(pp!=-1){
             
             printf("%c",p);
             pp = scanf("%c",&p);

              }
              
        clearerr(stdin);
             
         dup2(o, 0);

         close(o);

    }
   
    
    }


    return 0;

}

