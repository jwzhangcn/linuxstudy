#ifndef _TURING_H_
#define _TURING_H_

/*图灵机器人需要格式如下
{
	"reqType":0,					 //0表示用户传入的数据是文本信息，默认为0，可以不写
    "perception": {
        "inputText": {
            "text": "附近的酒店"    //用户传入的文本信息
        },
        "selfInfo": {
            "location": {
                "city": "北京",			//用户所在地，默认使用这个，除非在对话中修改
                "province": "北京",
                "street": "信息路"
            }
        }
    },
    "userInfo": {
        "apiKey": "",				//图灵网站上申请的key
        "userId": ""				//userId 随便写，我写的0
    }
}
*/

#define ERROR0     5000	//无解析结果
#define ERROR1     6000	//暂不支持该功能
#define ERROR2     4000	//请求参数格式错误
#define ERROR3     4001	//加密方式错误
#define ERROR4     4002	//无功能权限
#define ERROR5     4003	//该apikey没有可用请求次数
#define ERROR6     4005	//无功能权限
#define ERROR7     4007	//apikey不合法
#define ERROR8     4100	//userid获取失败
#define ERROR9     4200	//上传格式错误
#define ERROR10     4300	//批量操作超过限制
#define ERROR11     4400	//没有上传合法userid
#define ERROR12     4500	//userid申请个数超过限制
#define ERROR13     4600	//输入内容为空
#define ERROR14     4602	//输入文本内容超长(上限150)
#define ERROR15     7002	//上传信息失败
#define ERROR16     8008	//服务器错误

int SM_TuringInit(void);
int SM_TuringGetAns(char* in,char* out);

#endif
