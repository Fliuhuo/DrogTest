#ifndef DROGDOWNBOX_H
#define DROGDOWNBOX_H

#include "cocos2d.h"
#include "cocos-ext.h"

class DrogDownBox: public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    virtual bool init();  
   
    CREATE_FUNC(DrogDownBox);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	void set(cocos2d::CCString  buttonName,cocos2d::CCString  cellPictureName);
	void setpos(cocos2d::CCPoint pos);
	unsigned int getnum();
	void setButtonNum(int num1,int num2);
	void setPicScale(float num1,float num2);
	void _init_();

private:

	void onbuttonclick(CCObject* pSender);

	//
	cocos2d::extension::CCTableView* tableView;
	cocos2d::CCMenuItemImage *pTempImage;

	//my label
	cocos2d::CCLabelTTF * m_label;

	//two picture
	cocos2d::CCString m_cellPicturueName;
	cocos2d::CCString m_buttonPictureName;

	//result
	int m_num;

	//selector 
	cocos2d::CCLayer * m_father;
	cocos2d::SEL_MenuHandler m_selector;

	//the position
	cocos2d::CCPoint m_pos;

	//nums to show
	int m_shownum;
	int m_allnum;

	//two picture scale
	float m_cellScale;
	float m_buttonScale;
};


#endif