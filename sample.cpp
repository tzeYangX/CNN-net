#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h> 　
#include <sys/types.h> 
#include "TencentYoutuyun/ytopen_sdk.h"
#include "tinyxml.h"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/core/core_c.h"
TiXmlDocument *writeDoc;
TiXmlElement *RootElement;

using namespace std;
using namespace rapidjson;

int main(int argc,char * argv[])
{
	struct timeval tv1;
	struct timeval tv2;
         IplImage* img;
    //app sign params.
    ytopen_sdk::AppSign m_app_sign = 
    {
        10116783,
        "AKID75rTr2jsVu891gvMNBmALM9k7GBukksm",
        "rVv88vUqzveAUbVBdsthKm01oPmwsc8V",
        "914238489"
    };

    ytopen_sdk m_sdk;
    m_sdk.Init(m_app_sign);

    FILE * fp=fopen("/home/boon/log2.txt","r");
    char str[160];
    srand( (unsigned)time( NULL ) );
    int sd = rand()%10000;
    int num = 0;
    int errnum = 0;
    while(1)
 {
  if ( fgets(str,160,fp)==NULL) break;
     // usleep(1000);
      str[strlen(str)-1]='\0';   // 加一个字符串结束符
       num++;
	printf("%s  %d  err %d\n",str,num,errnum);
    img = cvLoadImage(str,CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
    rapidjson::Document result;
    gettimeofday(&tv1,NULL);
    if(0 != m_sdk.DetectFace(result,str))
    {
        cout << "DetectFace failed." << endl;
	errnum++;
	 ;cvReleaseImage(&img);continue;
    }
	
	gettimeofday(&tv2,NULL);
    printf("A************************** time is %d ms \n",tv2.tv_sec*1000 + tv2.tv_usec/1000 - tv1.tv_sec*1000 - tv1.tv_usec/1000);	
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    result.Accept(writer);
  
    cout << buffer.GetString() << endl;
    std::string dd = buffer.GetString();
    
    Document document;  
    document.Parse<0>(buffer.GetString());  

    Value &node1=document["tags"];  
    if(node1.Size() == 0) {
    char filepath[128];
    memset(filepath,0,128);
	   
         //   sprintf(filepath,"/home/boon/未分类/%d_%d.jpg",sd,num);
	//    printf("pp %d %d  %s \n",sd,num,filepath);
	 //   cvSaveImage(filepath,img);
    printf("size 0 \n");cvReleaseImage(&img); errnum ++;continue;

    }
	rapidjson::Value & val1 = node1[0];  
       rapidjson::Value & confidence1 = val1["confidence"];
         //   cout << confidence.GetDouble() << endl;
	
        float conf1 = confidence1.GetDouble();
	if(conf1 < 0.3)
	{
		printf("size OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");cvReleaseImage(&img); errnum ++;continue;
	}

    for (int i = 0; i < 1; ++i)  
        {   printf("w\n");
            rapidjson::Value & val = node1[i];  
	    rapidjson::Value & serial = val["serial"];
           // cout << serial.GetString() << endl;
	    std::string s1 = serial.GetString();
	    rapidjson::Value & brand = val["brand"];
           // cout << brand.GetString() << endl;
            std::string b1 = brand.GetString();
	    rapidjson::Value & type = val["type"];
          //  cout << type.GetString() << endl;
            std::string t1 = type.GetString();
	    rapidjson::Value & confidence = val["confidence"];
         //   cout << confidence.GetDouble() << endl;
            float conf = confidence.GetDouble();

	    rapidjson::Value & color = val["color"];
          //  cout << color.GetString() << endl;
            std::string c1 = color.GetString();
   	   // printf("w\n");
            char filepath[128];
	    memset(filepath,0,128);
	    sprintf(filepath,"/home/boon/qq1/brand/%s",b1.c_str());
  	    if(access(filepath, 0) == -1)  
	    {
		mkdir(filepath, 0777);  
	    }
      	    sprintf(filepath,"%s/%s",filepath,s1.c_str());
	    if(access(filepath, 0) == -1)  
	    {
		mkdir(filepath, 0777);  
	    }
            sprintf(filepath,"%s/%d%d.jpg",filepath,sd,num);
	    cvSaveImage(filepath,img);

	    memset(filepath,0,128);
	    sprintf(filepath,"/home/boon/qq1/type/%s",t1.c_str());
  	    if(access(filepath, 0) == -1)  
	    {
		mkdir(filepath, 0777);  
	    }
            sprintf(filepath,"%s/%d_%d.jpg",filepath,sd,num);
	   // printf("pp %d %d  %s \n",sd,num,filepath);
	    cvSaveImage(filepath,img);


	    memset(filepath,0,128);
	    sprintf(filepath,"/home/boon/qq1/color/%s",c1.c_str());
  	    if(access(filepath, 0) == -1)  
	    {
		mkdir(filepath, 0777);  
	    }
            sprintf(filepath,"%s/%d_%d.jpg",filepath,sd,num);
	  //  printf("pp %d %d  %s \n",sd,num,filepath);
	    cvSaveImage(filepath,img);
	    cvReleaseImage(&img);
        }  

     Value &node2=document["car_coord"];  
    for (int i = 0; i < 1; ++i)  
        {  
	   // printf("3tt\n");
            rapidjson::Value & val = node2;  
	    rapidjson::Value & x = val["x"];
            cout << x.GetDouble() << endl;
	    rapidjson::Value & y = val["y"];
            cout << y.GetDouble() << endl;
	    rapidjson::Value & width = val["width"];
            cout << width.GetDouble() << endl;
	    rapidjson::Value & height = val["height"];
            cout << height.GetDouble() << endl;


	    writeDoc = new TiXmlDocument; //xml文档指针
	
			//文档格式声明
			//TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "UTF-8", "yes");
			//writeDoc->LinkEndChild(decl); //写入文档

			int n = 3;	//父节点个数

			RootElement = new TiXmlElement("annotation");//根元素
			RootElement->SetAttribute("verified", "no"); //属性
			writeDoc->LinkEndChild(RootElement);
	
	
			TiXmlElement *folderElement = new TiXmlElement("folder");
			RootElement->LinkEndChild(folderElement);
			TiXmlText *folderContent = new TiXmlText("L");
			folderElement->LinkEndChild(folderContent);
		
			TiXmlElement *fileNameElement = new TiXmlElement("filename");
			RootElement->LinkEndChild(fileNameElement);
			TiXmlText *fileNameContent = new TiXmlText(str);
			fileNameElement->LinkEndChild(fileNameContent);
	
			TiXmlElement *pathElement = new TiXmlElement("path");
			RootElement->LinkEndChild(pathElement);
			TiXmlText *pathContent = new TiXmlText(str);
			pathElement->LinkEndChild(pathContent);
	
			TiXmlElement *sourceElement = new TiXmlElement("source");
			RootElement->LinkEndChild(sourceElement);
			TiXmlElement *databaseElement = new TiXmlElement("database");
			sourceElement->LinkEndChild(databaseElement);
			TiXmlText *databaseContent = new TiXmlText("Unknown");
			databaseElement->LinkEndChild(databaseContent);
	
			TiXmlElement *sizeElement = new TiXmlElement("size");
			RootElement->LinkEndChild(sizeElement);
			TiXmlElement *widthElement = new TiXmlElement("width");
			sizeElement->LinkEndChild(widthElement);
			TiXmlText *widthContent = new TiXmlText("960");
			widthElement->LinkEndChild(widthContent);
	
			TiXmlElement *heightElement = new TiXmlElement("height");
			sizeElement->LinkEndChild(heightElement);
			TiXmlText *heightContent = new TiXmlText("540");
			heightElement->LinkEndChild(heightContent);
	
			TiXmlElement *depthElement = new TiXmlElement("depth");
			sizeElement->LinkEndChild(depthElement);
			TiXmlText *depthContent = new TiXmlText("3");
			depthElement->LinkEndChild(depthContent);	

			TiXmlElement *segmentedElement = new TiXmlElement("segmented");
			RootElement->LinkEndChild(segmentedElement);
			TiXmlText *segmentedContent = new TiXmlText("0");
			segmentedElement->LinkEndChild(segmentedContent);



			    int xmin = (int)x.GetDouble() ;
			    int ymin = (int)y.GetDouble() ;
			    int xmax = (int)(xmin + width.GetDouble());
			    int ymax = (int)(ymin + height.GetDouble());
			
		       		std::stringstream streamIntToStr;
				streamIntToStr.str("");
				streamIntToStr<<xmax; 
				std::string xmaxString = streamIntToStr.str();
				
				streamIntToStr.str("");
				streamIntToStr<<xmin; 
				std::string xminString = streamIntToStr.str();
				
				streamIntToStr.str("");
				streamIntToStr<<ymax; 
				std::string ymaxString = streamIntToStr.str();  
				
				streamIntToStr.str("");    
				streamIntToStr<<ymin; 
				std::string yminString = streamIntToStr.str(); 
        
		
				TiXmlElement *objectElement = new TiXmlElement("object");
				RootElement->LinkEndChild(objectElement);
	    
				TiXmlElement *nameElement = new TiXmlElement("name");
				objectElement->LinkEndChild(nameElement);
				TiXmlText *nameContent = new TiXmlText("1");
				nameElement->LinkEndChild(nameContent);
	    
				TiXmlElement *poseElement = new TiXmlElement("pose");
				objectElement->LinkEndChild(poseElement);
				TiXmlText *poseContent = new TiXmlText("Unspecified");
				poseElement->LinkEndChild(poseContent);
	    
				TiXmlElement *truncatedElement = new TiXmlElement("truncated");
				objectElement->LinkEndChild(truncatedElement);
				TiXmlText *truncatedContent = new TiXmlText("0");
				truncatedElement->LinkEndChild(truncatedContent);
	    
				TiXmlElement *difficultElement = new TiXmlElement("difficult");
				objectElement->LinkEndChild(difficultElement);
				TiXmlText *difficultContent = new TiXmlText("0");
				difficultElement->LinkEndChild(difficultContent);	 
	    
				TiXmlElement *bndboxElement = new TiXmlElement("bndbox");
				objectElement->LinkEndChild(bndboxElement);
	    
	    
				TiXmlElement *xminElement = new TiXmlElement("xmin");
				bndboxElement->LinkEndChild(xminElement);
				TiXmlText *xminContent = new TiXmlText(xminString.c_str());
				xminElement->LinkEndChild(xminContent);
	    
				TiXmlElement *yminElement = new TiXmlElement("ymin");
				bndboxElement->LinkEndChild(yminElement);
				TiXmlText *yminContent = new TiXmlText(yminString.c_str());
				yminElement->LinkEndChild(yminContent);   
	    
				TiXmlElement *xmaxElement = new TiXmlElement("xmax");
				bndboxElement->LinkEndChild(xmaxElement);
				TiXmlText *xmaxContent = new TiXmlText(xmaxString.c_str());
				xmaxElement->LinkEndChild(xmaxContent);
	    
				TiXmlElement *ymaxElement = new TiXmlElement("ymax");
				bndboxElement->LinkEndChild(ymaxElement);
				TiXmlText *ymaxContent = new TiXmlText(ymaxString.c_str());
				ymaxElement->LinkEndChild(ymaxContent);

				std::string line(str);    
				line = line.replace(line.find("jpg"),3, "xml"); //从第一个@位置替换第一个@为空    
				writeDoc->SaveFile(line.c_str());
			     	delete writeDoc;
				// printf("3tt\n");
        }  
}
    return 0;
}
