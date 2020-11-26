#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turing.h"
#include <unistd.h>
#include <time.h>

#define CMD_INPUT_TEXT_OFFSET   108   //图灵json格式，字符串的位置
#define TR_CMD_MAX_LEN     512         //太小了装不下json格式命令内容
#define TR_RECV_MAX_LEN    1024        //太小了装不下json格式返回内容，具体随实际情况调整。
#define TL_RET_OK      10000	      //10000以上是正常的返回

/*私有图灵库*/
typedef struct {
	char key[32];
	char value0[64]; /*备选答案0*/
	char value1[64]; /*备选答案1*/
	char value2[64]; /*备选答案2*/
}T_USER_TR_DATA;
static T_USER_TR_DATA userTuringbase[] = {
	//{"你好","测试0","测试1","测试2"},
	{"嵌入式最帅","小华","是我，是我，还是我","除了我还会有别人吗？"},
	{"嵌入式培训哪家强","华清远见你最强","华清远见你最强","华清远见你最强"},
	{"你最喜欢谁","陶老板一直是我心里的最爱","我喜欢我，不一样的烟火","就不告诉你，就不告诉你"},
	{"西科大的同学帅不帅","帅的很","讨厌，非得我说出来吗","帅的冒烟烟"}
};

/*********************************************************************************  
* Description：  图灵模块初始化
* Input:         无
* Output:       无
* Return:       无
* Others:       无
**********************************************************************************/
int SM_TuringInit(void)
{
	srand((unsigned)time(NULL));/*随机种子*/
	return 0;
}

/*********************************************************************************  
* Description：  私有模块获取应答
* Input:         in：输入的问题
* Output:        out：输出私有的答案（用户保证数组空间足够）
* Return:       SM_OK：成功 ， SM_ERROR：失败
* Others:       
**********************************************************************************/
static int userGetAns(char* in,char* out)
{
	int i=0;
	int flag = 0;
	for(i=0;i<sizeof(userTuringbase)/sizeof(T_USER_TR_DATA);i++)
	{
		//printf("userGetAns in  is %s\n",in);
		//printf("userGetAns key is %s\n",userTuringbase[i].key);
		if(0 == strncmp(userTuringbase[i].key,in,strlen(userTuringbase[i].key)))
		{
			//printf("userGetAns value is get\n");
			/*随机取以值给key匹配*/
			int no = rand()%3;
			//printf("no is %d\n",no);
			char* p = (char*)(&(userTuringbase[i].value0))+no*64;
			//printf("p is %s\n",p);
			memcpy(out,p,64);
			//printf("out is %s\n",out);
			flag = 1;
			break;
		}
	}
	
	if(0 == flag)
	{
		return -1;
	}
	
	return 0;
}

/*********************************************************************************  
* Description：   字符串插入函数
* Input:         str：        被插入字符串，由使用者保证长度足够大能装载插入字符串大小。   
*				 pch:         待插入字符串
*				 pos：		  字符串插入str的pos下标之后
* Output:       无
* Return:       无
* Others:       无
**********************************************************************************/
static void trLink(char *str,char *pch, int pos)
{
	int i = 0;
	int j = 0;
	int len = strlen(str);
    int nlen = strlen(pch);
	for(i=len;i>pos;i--)  //把'\0'也包含进去
	{
		*(str+i+nlen)=*(str+i);
	}
	for(j=0;j<nlen;j++)
	{
		memcpy(str+pos+1,pch,nlen);
	}
}

/*********************************************************************************  
* Description：  图灵json解析，通过key值获取value值  
* Input:         str：解析的json字符串
*				 key：解析的key值
* Output:		 value： 匹配key的 value值
* Return:        SM_OK：成功  SM_ERROR：失败
* Others:       json key value格式如后：  key:value
**********************************************************************************/
static int trGetValue(char* str, char* key, char* value)
{
	char* pkey = NULL;
	char* begin = NULL;
	char* end = NULL;
	
	/*找到key开始的字符串*/
	pkey = strstr(str,key);
	if(NULL == pkey)
	{
		printf("key(%s) is not found\n",key);
		return -1;
	}
	printf("key(%s) found\n",key);
	
	/*找到value对应的开头*/
	begin = strchr(pkey,':');
	if(NULL == begin)
	{
		printf("begin(%s) is not found\n",begin);
		return -1;
	}
	printf("begin(%s) found\n",begin);
	
	/*找到value对应的结尾*/
	if(0==strncmp("code",key,4))
	{
		end = strchr(pkey,',');
	}
	else
	{
		end = strchr(pkey,'}');
	}
	if(NULL == end)
	{
		printf("end(%s) is not found\n",end);
		return -1;
	}
	printf("end(%s) found\n",end);
	
	//memset(value,0,sizeof(value));
	memcpy(value,begin+1,end-begin-1);
	printf("value len %d, data (%s) \n",end-begin-1,value);
	return 0;
}

//去掉指定字符
static void trSqueeze(char* s,char* out) 
{ 
    int i,j; 
    for (i = 0, j = 0; s[i] != '\0'; i++) 
    { 
        if ((s[i] != '\n') &&(s[i] != '\"')&&(s[i] != '\\'))
        { 
            out[j++] = s[i]; 
        } 
    } 
    out[j] = '\0';
} 


/*********************************************************************************  
* Description：  图灵模块获取应答
* Input:         in：输入的问题
* Output:        out：输出图灵机器人的答案（用户保证数组空间足够）
* Return:       SM_OK：成功 ， SM_ERROR：失败
* Others:       keyId,请使用自己申请的Id。在 apiKey后面
**********************************************************************************/
static int trGetAns(char* in,char* out)
{
	FILE* fp = NULL;
	char buf[TR_RECV_MAX_LEN] = {0};  //必须足够大，保证接收到全部的数据
	char tmpbuf[TR_RECV_MAX_LEN] = {0};
	int  tmpdata = 0;
	
	//printf("trGetAns in\n");
	
	/*初始化默认命令格式，必须是匹配的json格式，具体格式参见官网*/
	char cmd[TR_CMD_MAX_LEN] = "curl -l -H \"Content-type: application/json\" -X POST -d '{\"reqType\": 0, \"perception\": {\"inputText\": {\"text\": \"\"}, \"selfInfo\": {\"location\": {\"city\": \"成都\", \"province\": \"四川\", \"street\": \"科华北路99号\"}}}, \"userInfo\": {\"apiKey\": \"0cf3e1a9f2f442dca3bacc23b7e188bc\", \"userId\": \"0\"}}' http://openapi.tuling123.com/openapi/api/v2";
	
	/*组装命令*/
	trLink(cmd,in,CMD_INPUT_TEXT_OFFSET);
	printf("trLink cmd is (%s) \n",cmd);
	
	/*开启管道接收命令返回信息*/
	fp = popen(cmd, "r");
	if(!fp)
	{
		printf("SM_TuringGetAns popen is error\n");
		perror("popen");
		return -1;
	}
	
	fgets(buf,TR_RECV_MAX_LEN-1,fp);
	buf[TR_RECV_MAX_LEN-1]='\0';
	printf("buf is (%s) \n",buf);

	/*检测命令是否成功，解析code值*/
	trGetValue(buf,"code",tmpbuf);
	tmpdata = atoi(tmpbuf);
	if(tmpdata < TL_RET_OK)
	{
		printf("trGetValue no is error,no (%d)\n",tmpdata);
		return -1;
	}
	
	/*检测是否有文字信息*/
	trGetValue(buf,"\"text\":",tmpbuf);
	/*去掉""*/
	trSqueeze(tmpbuf,out);
	//memcpy(out,tmpbuf+1,strlen(tmpbuf)-2);
	//out[strlen(tmpbuf)-1] = '\0';

	pclose(fp);
	return 0;
}

/*********************************************************************************  
* Description：  获取应答
* Input:         in：输入的问题
* Output:        out：输出答案（用户保证数组空间足够）
* Return:       SM_OK：成功 ， SM_ERROR：失败
* Others:       先私有数据库，再图灵
**********************************************************************************/
int SM_TuringGetAns(char* in,char* out)
{
	int ret = 0;
	ret = userGetAns(in,out);
	if(-1 == ret)
	{
		trGetAns(in,out);
	}
	return 0;
}

int turing(char *order, char *out)
{
	char buf[1024];
	int ret = SM_TuringGetAns(order, buf);
	if(0 != ret)
	{
		printf("ack is %d\n",ret);
		return -1;
	}
	printf("outok is %s\n",buf);
	transcode(buf, out);
	
	return 0;
}

