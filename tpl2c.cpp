#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
int main(int dataCount,char *data[])
{
string fileName(data[1]);
string newFileName;
FILE *f1;
f1=fopen(fileName.c_str(),"rb");
if(f1==NULL)
{
return 0;
}
newFileName=fileName+".cpp";
string tmpFile=fileName;
int i,j,c;
if(tmpFile[0]>=97&&tmpFile[0]<=122)tmpFile[0]=tmpFile[0]-32;
for(i=1;tmpFile[i]!='.';i++);
tmpFile[i]='_';
i++;
while(tmpFile[i]!='\0')
{
if(tmpFile[i]>=97&&tmpFile[i]<=122)tmpFile[i]=tmpFile[i]-32;
i++;
}
tmpFile="get"+tmpFile;
FILE *f2;
f2=fopen(newFileName.c_str(),"wb");
if(f2==NULL)
{
return 0;
}
fputs("#include<tmwp>",f2);
fputs("\n",f2);
fputs("using namespace tmwp;",f2);
fputs("\n",f2);
fputs("void ",f2);
fputs(tmpFile.c_str(),f2);
fputs("(Request &request,Response &response)",f2);
fputs("\n",f2);
fputs("{",f2);
fputs("\n",f2);
int count=-1;
int r,len,k;
int found=0;
char str1[52];
char str2[52];
char str3[104];//due to overcome from error
str3[0]='\0';
while(1)
{
fgets(str1,51,f1);
if(feof(f1))break;
fflush(stdin);
len=strlen(str1);
if(str1[0]=='\n'||str1[0]=='\r')
{
continue;
}
else if(str1[len-1]=='\n')
{
str1[len-2]='\0';
}
else if(str1[len-1]=='\r')
{
str1[len-1]='\0';
}
fputs("response.write(",f2);
for(i=0,j=0;str1[i]!='\0';i++,j++)
{
if(str1[i]=='"')
{
str2[j]='\\';
j++;
}
if(strlen(str3)>0)
{
len=strlen(str3);
for(r=len-1;str1[i]!='\0'&&str1[i]!='$'&&str1[i]!='}';r++,i++)
{
str3[r]=str1[i];
}
str3[r]='\0';
if(str1[i]=='$')
{
fputs("\"",f2);
fputs(str3,f2);
fputs("\");",f2);
fputs("\n",f2);
i--;
}
else if(str1[i]=='\0')
{
fputs("\"",f2);
fputs(str3,f2);
fputs("\");",f2);
fputs("\n",f2);
}
else if(str1[i]=='}')
{
fputs("request.getValue(\"",f2);
fputs(str3,f2);
fputs("\"));",f2);
fputs("\n",f2);
}
count=-1;
str3[0]='\0';
continue;
}//(strlen(str3)>0) ends
str2[j]=str1[i];            //that's place to free from first $
if(str1[i]=='$'&&count==-1)
{
count=3;
if(str1[i+1]!='\0'&&str1[i+1]=='$')
{
count=2;
if(str1[i+2]!='\0'&&str1[i+2]=='$')
{
count=1;
if(str1[i+3]!='\0'&&str1[i+3]=='{')count=4;
else if(str1[i+3]!='\0')count=-1;
}
else if(str1[i+2]!='\0')count=-1;
}
else if(str1[i+1]!='\0')count=-1;
}

if((count==4)||(count==1&&str1[i]=='{')||(count==2&&str1[i]=='$'&&str1[i+1]=='{')||(count==3&&str1[i]=='$'&&str1[i+1]=='$'&&str1[i+2]=='{'))
{
if(count==4&&str1[0]!='$')
{
str2[j]='\0';
if(strlen(str2)>0)
{
fputs("\"",f2);
fputs(str2,f2);
fputs("\");",f2);
fputs("\n",f2);
}
for(j=0,k=i+count;str1[k]!='\0'&&str1[k]!='}';k++,j++)
{
str2[j]=str1[k];
}
str2[j]='#';
str2[j+1]='\0';
if(str1[k]=='\0'&&str1[k]!='}')
{
strcpy(str3,str2);
str2[0]='\0';
break;
}
else
{
fputs("response.write(",f2);
}
}  //if(count==4&&str1[0]!='$') ends
i+=(count);
for(c=0;str1[i]!='\0'&&str1[i]!='}';c++,i++)
{
str2[c]=str1[i];
}
str2[c]='\0';
count=-1;
str1[i]='\0';
if(strlen(str3)==0)
{
fputs("request.getValue(\"",f2);
fputs(str2,f2);
fputs("\"));",f2);
fputs("\n",f2);
j=-1;
if(str1[i+1]!='\0')fputs("response.write(",f2);
}
}//upper if condition ends
} //for loop ends
//done done
if(strlen(str1)>3&&count!=-1)//1=\0 2=\n 3=\r
{
str2[j-4+count]='\0';
if(strlen(str2)>0)
{
fputs("\"",f2);
fputs(str2,f2);
fputs("\");",f2);
fputs("\n",f2);
}
str1[0]='\0';
}
else if(strlen(str1)>3)//1=\0 2=\n 3=\r
{
str2[j]='\0';
if(strlen(str2)>0)
{
fputs("\"",f2);
fputs(str2,f2);
fputs("\");",f2);
fputs("\n",f2);
}
str1[0]='\0';
}
}//while loop ends
if(strlen(str1)>3)//1=\0 2=\n 3=\r
{
fputs("response.write(",f2);
fputs("\"",f2);
fputs(str1,f2);
fputs("\");",f2);
fputs("\n",f2);
}
fputs("}",f2);
fclose(f1);
fclose(f2);
FILE *f3;
f3=fopen("tpl.h","ab");
fseek(f3,0,2);
len=ftell(f3);
if(len==0)
{
fseek(f3,0,0);
fputs("#ifndef ___TPL",f3);
fputs("\n",f3);
fputs("#define ___TPL 123",f3);
fputs("\n",f3);
fputs("#include \"",f3);
fputs(newFileName.c_str(),f3);
fputs("\"",f3);
fputs("\n",f3);
fputs("#include<tmwp>",f3);
fputs("\n",f3);
fputs("using namespace tmwp;",f3);
fputs("\n",f3);
fputs("void ",f3);
fputs(tmpFile.c_str(),f3);
fputs("(Request &request,Response &response);",f3);
fputs("\n",f3);
fputs("void registerTPLs(TMWebProjector *server)",f3);
fputs("\n",f3);
fputs("{",f3);
fputs("\n",f3);
fputs("server->onRequest(\"/",f3);
fputs(fileName.c_str(),f3);
fputs("\",",f3);
fputs(tmpFile.c_str(),f3);
fputs(");",f3);
fputs("\n",f3);
fputs("}",f3);
fputs("\n",f3);
fputs("#endif",f3);
fclose(f3);
}
else
{
fclose(f3);
FILE *f4;
f4=fopen("tpl.h","rb");
FILE *f5;
f5=fopen("tmp.tmp","wb");
fgets(str1,50,f4);
fflush(stdin);
fputs(str1,f5);
fgets(str1,50,f4);
fflush(stdin);
fputs(str1,f5);
fputs("#include \"",f5);
fputs(newFileName.c_str(),f5);
fputs("\"",f5);
fputs("\n",f5);
fgets(str1,50,f4);
fflush(stdin);
while(1)
{
if(feof(f4))break;
if(strcmp(str1,"void registerTPLs(TMWebProjector *server)\n")==0)break;
fputs(str1,f5);
fgets(str1,50,f4);
fflush(stdin);
}
fputs("void ",f5);
fputs(tmpFile.c_str(),f5);
fputs("(Request &request,Response &response);",f5);
fputs("\n",f5);
fputs("void registerTPLs(TMWebProjector *server)",f5);
fputs("\n",f5);
fputs("{",f5);
fputs("\n",f5);
fputs("server->onRequest(\"/",f5);
fputs(fileName.c_str(),f5);
fputs("\",",f5);
fputs(tmpFile.c_str(),f5);
fputs(");",f5);
fputs("\n",f5);
fgets(str1,50,f4);
while(1)
{
fgets(str1,50,f4);
if(feof(f4))break;
fflush(stdin);
fputs(str1,f5);
}
fputs(str1,f5);
fclose(f4);
fclose(f5);
FILE *f6,*f7;
f6=fopen("tmp.tmp","rb");
f7=fopen("tpl.h","wb");
while(1)
{
fgets(str1,50,f6);
if(feof(f6))break;
fflush(stdin);
fputs(str1,f7);
}
fputs(str1,f7);
fclose(f6);
fclose(f7);
FILE *f8;
f8=fopen("tmp.tmp","wb");
fclose(f8);
}
return 0;
}