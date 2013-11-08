#include "MessageCenter.h"
#include <string>

MessageCenter* MessageCenter::instance = NULL;



class RecvStruct
{
public:
	CCObject* m_recvDelegate;
	int m_xyid;
	ConnectPackageFuncXY fun;
	bool removed;

	RecvStruct(CCObject* imp,int xyid,ConnectPackageFuncXY func)
	{
		removed = false;
		fun = func;
		m_recvDelegate = imp;
		m_xyid = xyid;
		if (m_recvDelegate)
		{
			m_recvDelegate->retain();
		}	
	}
	~RecvStruct()
	{
		if (m_recvDelegate)
		{
			m_recvDelegate->release();
		}

	}
};

class MessageStruct
{
public:
	CCObject* m_msgDelegate;
	MessageFunc fun;
	int msgid;
	CCObject* m_sender;
	bool removed;

	MessageStruct(CCObject *sender,CCObject* imp,MessageFunc func,int msg)
	{
		removed = false;
		fun = func;
		m_msgDelegate = imp;
		msgid = msg;
		m_sender = sender;
		if (m_msgDelegate)
		{
			m_msgDelegate->retain();
		}	
		if (m_sender)
		{
			//m_sender->retain();
		}
		
	}
	~MessageStruct()
	{
		if (m_msgDelegate)
		{
			m_msgDelegate->release();
		}
		if (m_sender)
		{
			//m_sender->release();
		}

	}
	
};


//POST
class PostDelay
{
public:
	CCObject* m_param;
	int msgid;
	CCObject* m_sender;


	PostDelay(CCObject *sender,int msg,CCObject* param)
	{
		msgid = msg;
		m_param = param;
		m_sender = sender;

		if (m_param)
			m_param->retain();
		if (m_sender)
		{
			//m_sender->retain();
		}
	}

	~PostDelay()
	{
		if (m_param)
			m_param->release();
		if (m_sender)
		{
			//m_sender->release();
		}
	}
};
//


MessageCenter::MessageCenter()
 {
	 DataPackageManager::shareDataPackageManager()->requestHandshake(datapackage_selector(MessageCenter::OnPackage),this);
	ixy = 0;
	 rsVector.clear();
	 msgVector.clear();
	m_pScheduler = 0;
	destory = 0;
	xyr = 0;
	msgisclean = 0;
	msgxycount = 0;
 }

void MessageCenter::clear()
{
	vector<RecvStruct*> rsVectorT = rsVector;
	vector<MessageStruct*> msgVectorT = msgVector;
	vector<PostDelay*> postVectorT = postVector;
	vector<RecvStruct*> rsVectorTempT = rsVectorTemp;
	vector<MessageStruct*> msgVectorTempT = msgVectorTemp;
	rsVector.clear();
	msgVector.clear();
	postVector.clear();
	rsVectorTemp.clear();
	msgVectorTemp.clear();



	vector<RecvStruct*>::iterator iter;
	for (iter=rsVectorT.begin();iter!=rsVectorT.end();iter++)
	{
		RecvStruct* r = *iter;
		delete r;
	}
	vector<MessageStruct*>::iterator iter2;
	for (iter2=msgVectorT.begin();iter2!=msgVectorT.end();iter2++)
	{
		MessageStruct* r = *iter2;
		delete r;
	}

	vector<PostDelay*>::iterator iter3;
	for (iter3=postVectorT.begin();iter3!=postVectorT.end();iter3++)
	{
		PostDelay* r = *iter3;
		delete r;
	}

	vector<RecvStruct*>::iterator iter4;
	for (iter4=rsVectorTempT.begin();iter4!=rsVectorTempT.end();iter4++)
	{
		RecvStruct* r = *iter4;
		delete r;
	}

	vector<MessageStruct*>::iterator iter5;
	for (iter5=msgVectorTempT.begin();iter5!=msgVectorTempT.end();iter5++)
	{
		MessageStruct* r = *iter5;
		delete r;
	}
}

MessageCenter::~MessageCenter()
{
	if (m_pScheduler != NULL)
	{
		m_pScheduler->unscheduleUpdateForTarget(this);
		m_pScheduler->release();
		m_pScheduler = 0;
	}
	DataPackageManager::purgeDataPackageManager();
	clear();
}


    /** Destroys the single instance of MessageCenter. */
void MessageCenter::purgeMessageCenter(void)
{
	
    CC_SAFE_RELEASE_NULL(instance);
	MessageCenter::instance = 0;
}

void MessageCenter::connectGame()
{
	//connect->DisConnect();
	DataPackageManager::shareDataPackageManager()->requestHandshake(datapackage_selector(MessageCenter::OnPackage),this);
}



// void MessageCenter::OnConnectEvent(int ev,int code,CConnect* sender)
// {
// 	// ev=1 success
// 	// ev=4 fail
// 	// ev=3 OK
// 	//char aa[] = {0x01,0x01,0x01,0x00,0x00,0x00,0x0a,0x00,0x36,0x32,0x36,0x35,0x32,0x37,0x34,0x34,0x38,0x31,0x00,0xf3,0xe0,0x01,0x00,0x28,0x00,0x33,0x34,0x32,0x38,0x31,0x37,0x37,0x45,0x43,0x31,0x46,0x30,0x32,0x32,0x35,0x46,0x36,0x43,0x43,0x39,0x42,0x31,0x45,0x34,0x45,0x36,0x45,0x46,0x44,0x46,0x42,0x34,0x41,0x32,0x32,0x38,0x31,0x42,0x34,0x36,0x01,0x00};
// 	//connect->SendPackage(aa,sizeof(aa));
// 	
// 	if(ev==1&&code==0)
// 		postMessage(NULL,MESSAGE_CONNECT_OK,NULL);
// 	else if(ev==1&&code!=0)
// 		postMessage(NULL,MESSAGE_CONNECT_FAIL,NULL);
// 	else if(ev==4)
// 	{
// 		
// 		postMessage(NULL,MESSAGE_CONNECT_CLOSE,NULL);
// 	}
// }

void MessageCenter::OnPackage(void* data,void* route)
{
	int i = (int)route;
	postNotification(data,i);
}

//****** 协议监听
void MessageCenter::addRecvObserver(CCObject *target,int xyid,ConnectPackageFuncXY fun)
{
	vector<RecvStruct*>::iterator iter;
	for (iter=rsVector.begin();iter!=rsVector.end();iter++)
	{
		RecvStruct* r = *iter;
		if (r->m_xyid == xyid && r->m_recvDelegate == target)
		{
			return;
		}
	}

	for (iter=rsVectorTemp.begin();iter!=rsVectorTemp.end();iter++)
	{
		RecvStruct* r = *iter;
		if (r->m_xyid == xyid && r->m_recvDelegate == target)
		{
			return;
		}
	}
	RecvStruct* rs = new RecvStruct(target,xyid,fun);
	rsVectorTemp.push_back(rs);
}
void MessageCenter::removeRecvObserver(CCObject *target,int xyid)
{
	if (ixy > 0)
	{
		vector<RecvStruct*>::iterator iter;
		for (iter=rsVector.begin();iter!=rsVector.end();iter++)
		{
			RecvStruct* r = *iter;
			if (r->m_xyid == xyid && r->m_recvDelegate == target)
			{
				xyr++;
				r->removed = true;
				break;
			}
		}

		for (iter=rsVectorTemp.begin();iter!=rsVectorTemp.end();iter++)
		{
			RecvStruct* r = *iter;
			if (r->m_xyid == xyid && r->m_recvDelegate == target)
			{
				xyr++;
				r->removed = true;
				break;
			}
		}
	}
	else
	{
		vector<RecvStruct*>::iterator iter;
		for (iter=rsVector.begin();iter!=rsVector.end();iter++)
		{
			RecvStruct* r = *iter;
			if (r->m_xyid == xyid && r->m_recvDelegate == target)
			{

				delete r;
				rsVector.erase(iter);
				break;
			}
		}

		for (iter=rsVectorTemp.begin();iter!=rsVectorTemp.end();iter++)
		{
			RecvStruct* r = *iter;
			if (r->m_xyid == xyid && r->m_recvDelegate == target)
			{

				delete r;
				rsVectorTemp.erase(iter);
				break;
			}
		}
	}
	

}
 void MessageCenter::removeAllRecvObserver(CCObject* listen)
 {
	 vector<RecvStruct*>::iterator iter;
	 for (iter=rsVector.begin();iter!=rsVector.end();iter++)
	 {
		 RecvStruct* r = *iter;
		 if (r->m_recvDelegate == listen)
			{
				xyr++;
				r->removed = true;
			}
	 }

	 for (iter=rsVectorTemp.begin();iter!=rsVectorTemp.end();iter++)
	 {
		 RecvStruct* r = *iter;
		 if (r->m_recvDelegate == listen)
			{
				xyr++;
				r->removed = true;
			}
	 }
 }

void MessageCenter::postNotification(void* p,int route)
{
	
	if (rsVectorTemp.size()>0)
	{
		vector<RecvStruct*>::iterator riter;
		for (riter=rsVectorTemp.begin();riter!=rsVectorTemp.end();riter++)
		{
			RecvStruct* r = *riter;
			rsVector.push_back(r);
		}
		rsVectorTemp.clear();
	}
	vector<RecvStruct*>::iterator iter;
	for (iter=rsVector.begin();iter!=rsVector.end();iter++)
	{
		RecvStruct* r = *iter;
		if (r->m_xyid == route && r->removed == false)
		{
			ixy++;
			(r->m_recvDelegate->*(r->fun))(route,p);
			ixy--;
		}
	}
	if (xyr>0)
	{
		vector<RecvStruct*>::iterator riter;
		for (riter=rsVector.begin();riter!=rsVector.end();)
		{
			RecvStruct* r = *riter;
			if (r->removed)
			{
				riter = rsVector.erase(riter);
				delete r;
			}
			else
				riter++;
		}
		xyr = 0;
	}
}


//****** 系统监听
void MessageCenter::addMsgObserver(CCObject *sender,CCObject *listen,int listenmsgid,MessageFunc listenfun)
{
	if(m_pScheduler==0){
		m_pScheduler = CCDirector::sharedDirector()->getScheduler();
		m_pScheduler->retain();
		m_pScheduler->scheduleUpdateForTarget(this,0,false);
	}

	
	bool hasSame = false;
	vector<MessageStruct*>::iterator iter;
	for (iter=msgVector.begin();iter!=msgVector.end();iter++)
	{
		MessageStruct* r = *iter;
		if (r->msgid == listenmsgid && r->m_msgDelegate == listen && sender == r->m_sender)
		{
			hasSame = true;
			break;
		}
	}
	for (iter=msgVectorTemp.begin();iter!=msgVectorTemp.end();iter++)
	{
		MessageStruct* r = *iter;
		if (r->msgid == listenmsgid && r->m_msgDelegate == listen && sender == r->m_sender)
		{
			hasSame = true;
			break;
		}
	}

	if (hasSame == false)
	{
		MessageStruct* msg = new MessageStruct(sender,listen,listenfun,listenmsgid);
		msgVectorTemp.push_back(msg);
	}
	

}
void MessageCenter::removeMsgObserver(CCObject *sender,CCObject *listen,int listenmsgid)
{
	if (msgxycount>0)
	{

		vector<MessageStruct*>::iterator iter;
		//int rem=0;
		for (iter=msgVector.begin();iter!=msgVector.end();iter++)
		{
			MessageStruct* r = *iter;
			if (r->msgid == listenmsgid && r->m_msgDelegate == listen && sender == r->m_sender)
			{
				msgisclean++;
				r->removed=true;
				
		
				break;
			}
		}
		for (iter=msgVectorTemp.begin();iter!=msgVectorTemp.end();iter++)
		{
			MessageStruct* r = *iter;
			if (r->msgid == listenmsgid && r->m_msgDelegate == listen && sender == r->m_sender)
			{
				msgisclean++;
				r->removed=true;

				break;
			}
		}
	}
	else
	{
		vector<MessageStruct*>::iterator iter;
		//int rem=0;
		for (iter=msgVector.begin();iter!=msgVector.end();iter++)
		{
			MessageStruct* r = *iter;
			if (r->msgid == listenmsgid && r->m_msgDelegate == listen && sender == r->m_sender)
			{

				delete r;
				msgVector.erase(iter);


				break;
			}
		}
		for (iter=msgVectorTemp.begin();iter!=msgVectorTemp.end();iter++)
		{
			MessageStruct* r = *iter;
			if (r->msgid == listenmsgid && r->m_msgDelegate == listen && sender == r->m_sender)
			{
				delete r;
				msgVectorTemp.erase(iter);

				break;
			}
		}
	}
	
	
}
void MessageCenter::removeAllMsgObserver(CCObject *listen)
{

	vector<MessageStruct*>::iterator iter;
	//int rem=0;
	for (iter=msgVector.begin();iter!=msgVector.end();iter++)
	{
		MessageStruct* r = *iter;
		if (r->m_msgDelegate == listen)
		{
			msgisclean++;
			r->removed=true;



		}
	}
	for (iter=msgVectorTemp.begin();iter!=msgVectorTemp.end();iter++)
	{
		MessageStruct* r = *iter;
		if (r->m_msgDelegate == listen )
		{
			msgisclean++;
			r->removed=true;


		}
	}
}
void MessageCenter::postMessage(CCObject *sender,int msgid,CCObject* param)
{
	if(m_pScheduler==0){
		m_pScheduler = CCDirector::sharedDirector()->getScheduler();
		m_pScheduler->retain();
		m_pScheduler->scheduleUpdateForTarget(this,0,false);
	}
	postVector.push_back(new PostDelay(sender,msgid,param));
	

}

void MessageCenter::update(float dt)
{
	

	vector<MessageStruct*>::iterator miter;
	for (miter=msgVectorTemp.begin();miter!=msgVectorTemp.end();miter++)
	{
		MessageStruct* r = *miter;
		msgVector.push_back(r);
	}
	msgVectorTemp.clear();


	
	


	if (postVector.size() == 0)
		return;


	vector<PostDelay*>postCopy(postVector);
	vector<MessageStruct*> msgCopy(msgVector);
	postVector.clear();

	vector<PostDelay*>::iterator iter3;
	for (iter3=postCopy.begin();iter3!=postCopy.end();++iter3)
	{
		PostDelay* pd = *iter3;
		
	
		// 发送每条消息

		
		vector<MessageStruct*>::iterator iter;
		for (iter=msgCopy.begin();iter!=msgCopy.end();++iter)
		{
			MessageStruct* r = *iter;
			if (r->msgid == pd->msgid && (r->m_sender == NULL ||r->m_sender == pd->m_sender) && r->removed == false)
			{
				msgxycount++;
				(r->m_msgDelegate->*(r->fun))(pd->m_sender,pd->msgid,pd->m_param);
				msgxycount--;
			}
		}

		delete pd;
	}
	postCopy.clear();
	msgCopy.clear();
	if (msgisclean>0)
	{
		for (miter=msgVector.begin();miter!=msgVector.end();)
		{
			MessageStruct* r = *miter;
			if (r->removed)
			{
				miter = msgVector.erase(miter);
				delete r;
			}
			else
				miter++;
		}
		msgisclean =0;
	}
	
}


