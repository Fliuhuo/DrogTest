#include "DrogDownBox.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool DrogDownBox::init()
{
	m_num = 1;
	m_pos = ccp(0,0);
	m_shownum = 5;
	m_allnum = 10;
	m_cellScale = 1;
	m_buttonScale = 1;
	return true;
}

void DrogDownBox::setpos(CCPoint pos)
{
	m_pos = pos;
}

unsigned int DrogDownBox::getnum()
{
	return  m_num;
}

void DrogDownBox::setButtonNum(int num1,int num2)
{
	m_shownum = num1;
	m_allnum = num2;
}
	
void DrogDownBox::setPicScale(float num1,float num2)
{
	m_cellScale = num1;
	m_buttonScale = num2;
}

void DrogDownBox::set(cocos2d::CCString  buttonName,cocos2d::CCString  cellPictureName)
{
	m_cellPicturueName = cellPictureName;
	m_buttonPictureName = buttonName;
}

void DrogDownBox::_init_()
{
	pTempImage = CCMenuItemImage::create(m_buttonPictureName.getCString(),m_buttonPictureName.getCString(),
			this,menu_selector(DrogDownBox::onbuttonclick));
	pTempImage->setPosition(m_pos);
	pTempImage->setAnchorPoint(ccp(0,0));
	pTempImage->setScale(m_buttonScale);
	CCMenu* pMenuTempImage = CCMenu::create(pTempImage,NULL);
	pMenuTempImage->setPosition(CCPointZero);
	this->addChild(pMenuTempImage,NULL);

	m_label = CCLabelTTF::create("1", "Helvetica", 20.0);
	m_label->setPosition(ccp(pTempImage->getPosition().x+ pTempImage->getContentSize().width*0.5*m_buttonScale,pTempImage->getPosition().y));
	m_label->setAnchorPoint(ccp(0.5,0));
	this->addChild(m_label);


	CCSprite *sprite = CCSprite::create(m_cellPicturueName.getCString());

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	tableView = CCTableView::create(this, CCSizeMake(sprite->getContentSize().width*m_cellScale, sprite->getContentSize().height*m_cellScale*m_shownum));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(pTempImage->getPosition().x,pTempImage->getPosition().y-sprite->getContentSize().height*m_cellScale*m_shownum);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView);
	tableView->reloadData();
	tableView->setVisible(false);
}

void DrogDownBox::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx()+1);
	CCString *string = CCString::createWithFormat("%d", cell->getIdx()+1);
	m_num = cell->getIdx()+1;
	m_label->setString(string->getCString());
	//todo this may cause error 
	//tableView->setVisible(false);
}

CCSize DrogDownBox::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(pTempImage->getContentSize().width*m_buttonScale, pTempImage->getContentSize().height*m_buttonScale);
}

CCTableViewCell* DrogDownBox::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx+1);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell)
	{
        cell = new CCTableViewCell();
        cell->autorelease();
		CCSprite *sprite = CCSprite::create(m_cellPicturueName.getCString());
		sprite->setScale(m_cellScale);
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);

        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setPosition(ccp(sprite->getPosition().x + sprite->getContentSize().width*m_cellScale*0.5,sprite->getPosition().y + sprite->getContentSize().height*m_cellScale*0.5));
		label->setAnchorPoint(ccp(0.5,0.5));
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }

    return cell;
}

unsigned int DrogDownBox::numberOfCellsInTableView(CCTableView *table)
{
    return m_allnum;
}

void DrogDownBox::onbuttonclick(CCObject* pSender)
{
	if(tableView->isVisible())
	{
		tableView->setVisible(false);
	}
	else
	{
		tableView->setVisible(true);
	}
}

