#ifndef __MDSJ_ZLL_DEFINE_H__
#define __MDSJ_ZLL_DEFINE_H__


#define DEF_FONT_NAME	"Arial"

#define LAYER_UILAYER_ZINDEX 5		//各个层上UI层的层次
#define LAYER_POPWINDOW		10

enum ButtomType//按钮类型
{
	ButtomType_Red=1,
	ButtomType_Blue1,
	ButtomType_Blue2,
	ButtomType_Blue3,
	ButtomType_Blue4,
	ButtomType_Replace,	//更换
};

enum FightType//战斗类型
{
	FightType_NULL=0,
	FightType_PVP=1,
	FightType_PVE,
	FightType_PVBOSS,
};

enum FightElementNodeType//战斗元素类型
{
	FightElementNodeType_Player=1,
	FightElementNodeType_Monster,
};

enum PVEFightType//PVE战斗类型
{
	PVEFightType_NULL=0,
	PVEFightType_MONSTER,
	PVEFightType_BOSS,
};

enum GameRoom_PlayerNodeType
{
	GameRoom_PlayerNodeType_Empty=0,
	GameRoom_PlayerNodeType_Master,
	GameRoom_PlayerNodeType_CommonPlayer,
	GameRoom_PlayerNodeType_Closed,
};

//图片文件文件路径
#define PICPATH_AREMAPATH "ui/Arema/"

//重复纹理
#define REPEATTEXTURE_1 "ui/repeattexture/repeat_1.png"

//竞技场资源
#define ATHLETIC_1V1 "ui/Arema/1v1.png"
#define ATHLETIC_BUTTON_1_1 "ui/Arema/athletic_button1_1.png"	//返回按钮
#define ATHLETIC_BUTTON_1_2 "ui/Arema/athletic_button1_2.png"	//返回按钮
#define ATHLETIC_BUTTON_1_3 "ui/Arema/athletic_button1_3.png"	//返回按钮

#define ATHLETIC_BUTTON_2_1 "ui/Arema/athletic_button2_1.png"	//查找玩家按钮
#define ATHLETIC_BUTTON_2_2 "ui/Arema/athletic_button2_2.png"	//查找玩家按钮
#define ATHLETIC_BUTTON_2_3 "ui/Arema/athletic_button2_3.png"	//查找玩家按钮

#define ATHLETIC_BUTTON_3_1 "ui/Arema/athletic_button3_1.png"	//快速加入按钮
#define ATHLETIC_BUTTON_3_2 "ui/Arema/athletic_button3_2.png"	//快速加入按钮
#define ATHLETIC_BUTTON_3_3 "ui/Arema/athletic_button3_3.png"	//快速加入按钮

#define ATHLETIC_BUTTON_4_1 "ui/Arema/athletic_button4_1.png"	//道具购买按钮
#define ATHLETIC_BUTTON_4_2 "ui/Arema/athletic_button4_2.png"	//道具购买按钮
#define ATHLETIC_BUTTON_4_3 "ui/Arema/athletic_button4_3.png"	//道具购买按钮

#define ATHLETIC_BUTTON_5_1 "ui/Arema/athletic_button5_1.png"	//好友按钮
#define ATHLETIC_BUTTON_5_2 "ui/Arema/athletic_button5_2.png"	//好友按钮
#define ATHLETIC_BUTTON_5_3 "ui/Arema/athletic_button5_3.png"	//好友按钮

#define ATHLETIC_BUTTON_REPLACE_1 "ui/Arema/athletic_replace_1.png"
#define ATHLETIC_BUTTON_REPLACE_2 "ui/Arema/athletic_replace_2.png"
#define ATHLETIC_BUTTON_REPLACE_3 "ui/Arema/athletic_replace_3.png"

#define ATHLETIC_ICON_ITEM_001 "ui/Arema/athletic_icon_item001.png" //道具图标
#define ATHLETIC_ICON_MAP_001 "ui/Arema/athletic_icon_map001.png"	//战斗地图的图标
#define ATHLETIC_ICON_MAPDIFFICULTY "ui/Arema/athletic_icon_mapdifficulty.png" //地图难度图标
#define ATHLETIC_ICON_ROOMLOCK "ui/Arema/athletic_icon_roomlock.png" //锁的图标
#define ATHLETIC_ICON_SOUL_001 "ui/Arema/athletic_icon_soul001.png" //魂魄图标
#define ATHLETIC_LABEL_PLAYERMESSAGE "ui/Arema/athletic_labe_playermessage.png"	//玩家信息标签
#define ATHLETIC_LABEL_ITEM_001 "ui/Arema/athletic_label_item001.png"	//道具文本描述
#define ATHLETIC_LABEL_SOUL_001 "ui/Arema/athletic_label_soul001.png"	//魂魄文本描述
#define ATHLETIC_LIST_MAP "ui/Arema/athletic_list_map.png" //战斗地图的菜单选项
#define ATHLETIC_LIST_PLAYER "ui/Arema/athletic_list_player.png" //玩家列表选项
#define ATHLETIC_LIST_ROOM "ui/Arema/athletic_list_room.png" //房间选择菜单项
#define ATHLETIC_LIST_TYPE "ui/Arema/athletic_list_type.png" //模式选择菜单项
#define ATHLETIC_PIC_FEMALEPLAYER "ui/Arema/athletic_pic_femaleplayer.png" //女性玩家形象
#define ATHLETIC_PIC_MALEPLAYER "ui/Arema/athletic_pic_maleplayer.png" //男性玩家形象
#define ATHLETIC_SCROORBAR "ui/Arema/athletic_scroorbar.png" //垂直滚动条
#define ATHLETIC_TEXTINPUTS_ROOMCODE "ui/Arema/athletic_textinputs_roomcode.png" //房间密码的文本输入框
#define ATHLETIC_TYPE_ICON_1 "ui/Arema/athletic_type_icon1.png" //生存模式的图标
#define ATHLETIC_TYPE_ICON_2 "ui/Arema/athletic_type_icon2.png" //塔防模式的图标
#define ATHLETIC_TYPE_ICON_3 "ui/Arema/athletic_type_icon3.png" //对抗模式的图标
#define ATHLETIC_TYPE_ICON_4 "ui/Arema/athletic_type_icon4.png" //探索模式的图标
#define ATHLETIC_PROPS_2 "ui/Arema/Props2.png" //道具2
#define ATHLETIC_BACKGROUND "ui/Arema/Background.png" //底
#define ATHLETIC_BACKGROUNDSMALL "ui/Arema/BackgroundSmall.png" //底小
#define ATHLETIC_BACKGROUNDSMALL_1 "ui/Arema/BackgroundSmall_1.png" //底小1

#define ATHLETIC_ROOM_ID "ui/Arema/athletic_room_id.png" //房间ID
#define ATHLETIC_ROOM_MAP "ui/Arema/athletic_map.png" //地图

#define ATHLETIC_POPWINBACKGROUND_2 "ui/Arema/PopWinBackground2.png"

#define ATHLETIC_TEXTURE "ui/Arema/Texture.png"
#define ATHLETIC_TEXTURE_2 "ui/Arema/Texture2.png"
#define ATHLETIC_PLAYERHEADER "ui/Arema/athletic_playerheader.png"  //玩家头像

//PVE
#define PVE_FIELD_MAP "ui/PVE/field_map.png"								//野外地图
#define PVE_FIELD_PULLDOWNLIST  "ui/PVE/field_pulldownlist.png"				//下拉列表
#define PVE_FIELD_BUTTON_MAPNAME  "ui/PVE/field_button_mapname.png"			//地图名
#define PVE_FIELD_BUTTON_MAPNAME_SEL  "ui/PVE/field_button_mapname_sel.png"	//选中的地图名
#define PVE_FIELD_BUTTON_MAPNAME_NOT  "ui/PVE/field_button_mapname_not.png"
#define PVE_FIELD_LABEL_LV  "ui/PVE/field_label_lv.png"						//地图等级的标签
#define PVE_FIELD_BUTTON_STAGE  "ui/PVE/field_button_stage.png"				//PVE关卡建筑按钮
#define PVE_FIELD_BUTTON_STAGE_SEL "ui/PVE/field_button_stage_sel.png"			//按住状态的PVE关卡建筑按钮
#define PVE_FIELD_PIC_ROAD  "ui/PVE/field_pic_road.png"							//PVE关卡路线图标，正常颜色的路线
#define PVE_FIELD_PIC_ROAD_OK  "ui/PVE/field_pic_road_ok.png"				//PVE关卡路线图标，灰色的路线
#define PVE_FIELD_LABEL_STAGEAME  "ui/PVE/field_label_stagename.png"		//关卡地名的标签
#define PVE_FIELD_PIC_STAR_1  "ui/PVE/field_pic_star1.png"					//战斗评价的星星
//#define PVE_FIELD_PIC_STAR_2  "ui/PVE/field_pic_star2.png"					//战斗评价的星星
#define PVE_FIELD_BUTTON_ARROW  "ui/PVE/field_button_arrow.png"				//左右切换地图的箭头
#define PVE_FIELD_BUTTON_1  "ui/PVE/field_button1.png"						//文字按钮
#define PVE_FIELD_BUTTON_1_SEL  "ui/PVE/field_button1_sel.png"				//按住文本按钮
#define PVE_FIELD_BUTTON_1_NOT  "ui/PVE/field_button1_not.png"				//灰色文本按钮
#define PVE_FIELD_PIC_STAGEPROMPT  "ui/PVE/field_pic_stageprompt.png"		//关卡提示图片
#define PVE_FIELD_BGPIC_STAGEMESSAGE  "ui/PVE/field_bgpic_stagemessage.png"	//关卡信息的背景图
//#define PVE_FIELD_LABEL_1_STAGE  "ui/PVE/field_label_stage.png"				//关卡的信息标签
#define PVE_FIELD_PIC_GROOVE  "ui/PVE/field_pic_groove.png"					//关卡掉落品的凹槽
#define PVE_FIELD_BUTTON_2  "ui/PVE/field_button2.png"						//文字按钮
#define PVE_FIELD_BUTTON_2_SEL  "ui/PVE/field_button2_sel.png"				//按住文字按钮
#define PVE_FIELD_BUTTON_2_NOT  "ui/PVE/field_button2_not.png"					//灰色文字按钮
#define PVE_FIELD_SCROORBAR  "ui/PVE/field_scroorbar.png"					//垂直滚动条
#define PVE_FIELD_BGPIC_HOME  "ui/PVE/field_bgpic_home.png"					//组队房间的背景图
#define PVE_FIELD_PIC_STAGE  "ui/PVE/field_pic_stage.png"					//关卡场景图
#define PVE_FIELD_PIC_VIPLV  "ui/PVE/field_pic_viplv.png"					//VIP等级图标
#define PVE_FIELD_BUTTON_SEAT_1  "ui/PVE/field_button_seat1.png"			//玩家座位开启状态
#define PVE_FIELD_BUTTON_SEAT_1_SEL  "ui/PVE/field_button_seat1_sel.png"	//按住开启状态的座位按钮
#define PVE_FIELD_BUTTON_SEAT_2  "ui/PVE/field_button_seat2.png"			//玩家座位关闭状态
#define PVE_FIELD_BUTTON_SEAT_2_SEL  "ui/PVE/field_button_seat2_sel.png"	//按住关闭状态的座位按钮
#define PVE_FIELD_PIC_RANKSLOCK  "ui/PVE/field_pic_rankslock.png"			//队伍状态
#define PVE_FIELD_PIC_ROAD_1  "ui/PVE/field_pic_road1.png"					//关卡间道路，实线
#define PVE_FIELD_PIC_ROAD_2  "ui/PVE/field_pic_road2.png"					//关卡间道路，虚线
#define PVE_FIELD_PIC_STAGELOCK  "ui/PVE/field_pic_stagelock.png"			//关卡锁按钮
#define PVE_FIELD_BUTTON_3  "ui/PVE/field_button3.png"						//文字按钮
#define PVE_FIELD_PIC_PLAYER  "ui/PVE/field_pic_player.png"					//玩家形象
#define PVE_FIELD_BUTTON_4  "ui/PVE/field_button4.png"						//魂魄调整按钮
#define PVE_FIELD_BUTTON_4_SEL  "ui/PVE/field_button4_sel.png"				//按住魂魄调整按钮
#define PVE_FIELD_BUTTON_5  "ui/PVE/field_button5.png"						//返回按钮
#define PVE_FIELD_BUTTON_5_SEL  "ui/PVE/field_button5_sel.png"				//返回按钮
#define PVE_FIELD_BUTTON_6  "ui/PVE/field_button6.png"						//邀请按钮
#define PVE_FIELD_BUTTON_6_SEL  "ui/PVE/field_button6_sel.png"				//邀请按钮
#define PVE_FIELD_BGPIC_TEAMNAMETEXT  "ui/PVE/field_bgpic_teamnametext.png"	//文本输入框的背景图
#define PVE_FIELD_BGPIC_PLAYERLIST  "ui/PVE/field_bgpic_playerlist.png"		//玩家列表背景框
#define PVE_FIELD_BGPIC_PLAYERNAME_WIN  "ui/PVE/field_bgpic_playername_win.png"//胜利玩家名称牌匾背景图
#define PVE_FIELD_BGPIC_PLAYERNAME_LOSE  "ui/PVE/field_bgpic_playername_lose.png"//失败玩家名称牌匾背景图
#define PVE_FIELD_BGPIC_WIN  "ui/PVE/fieeld_bgpic_win.png"					//胜利台子背景图
#define PVE_FIELD_BGPIC_LOSE  "ui/PVE/fieeld_bgpic_lose.png"				//失败台子背景图
#define PVE_FIELD_PIC_MALEPLAYER_1_WIN  "ui/PVE/field_pic_maleplayer1_win.png"//玩家胜利图片
#define PVE_FIELD_PIC_MALEPLAYER_1_LOSE  "ui/PVE/field_pic_maleplayer1_lose.png"//玩家失败图标
#define PVE_FIELD_PIC_MALEPLAYER_2_WIN  "ui/PVE/field_pic_maleplayer2_win.png"//玩家胜利图片
#define PVE_FIELD_PIC_MALEPLAYER_2_LOSE  "ui/PVE/field_pic_maleplayer2_lose.png"//玩家失败图标
#define PVE_FIELD_PIC_FEMALEPLAYER_1_WIN  "ui/PVE/field_pic_femaleplayer1_win.png"//玩家胜利图片
#define PVE_FIELD_PIC_FEMALEPLAYER_1_LOSE  "ui/PVE/field_pic_femaleplayer1_lose.png"//玩家失败图标
#define PVE_FIELD_PIC_FEMALEPLAYER_2_WIN  "ui/PVE/field_pic_femaleplayer2_win.png"//玩家胜利图片
#define PVE_FIELD_PIC_FEMALEPLAYER_2_LOSE  "ui/PVE/field_pic_femaleplayer2_lose.png"//玩家失败图标
#define PVE_FIELD_BGPIC_BATTLEEND  "ui/PVE/fiel_bgpic_battleend.png"		//战斗结算表背景图
#define PVE_FIELD_CARD_FRONT  "ui/PVE/field_card_front.png"					//战斗结算的卡牌正面
#define PVE_FIELD_CARD_BACK  "ui/PVE/field_card_back.png"	
#define PVE_FIELD_FIELD_SEARCHTEAM_INPUTID  "ui/PVE/field_searchteam_inputId.png"
#define PVE_FIELD_POPWIN_BACKGROUND "ui/PVE/field_popwin_background.png"
#define PVE_FIELD_GAMEROOM_READY  "ui/PVE/field_gameroom_ready.png"
#define PVE_FIELD_GAMEROOM_MASTER  "ui/PVE/field_gameroom_master.png"
#define PVE_FIELD_BUTTON_MAPNAME_1  "ui/PVE/field_button_mapname1.png"
//战斗结算的卡牌背面

//战斗资源
#define FIGHT_BGPIC_ITEMSOUL "ui/fight/fight_bgpic_itemsoul.png"						//道具和魂魄的图标凹槽
#define FIGHT_BGPIC_LEAVE "ui/fight/fight_bgpic_leave.png"								//退出2次确认框的背景
#define FIGHT_BGPIC_MAP "ui/fight/fight_bgpic_map.png"										//战斗背景图,不可破坏的地形
#define FIGHT_BGPIC_BACKGROUND "ui/fight/fight_pic_background.png"						//战斗背景
#define FIGHT_BGPIC_PLAYERORDER "ui/fight/fight_bgpic_playerorder.png"					//玩家行动顺序信息背景图
#define FIGHT_LABEL_ABILITYDOWN_ATTACK "ui/fight/fight_label_abilitydown_attack.png"	//攻击力下降标签
#define FIGHT_LABEL_ABILITYDOWN_DEFENCE "ui/fight/fight_label_abilitydown_defence.png"	//防御力下降标签
#define FIGHT_LABEL_ABILITYDOWN_HP "ui/fight/fight_label_abilitydown_hp.png"			//HP减少标签
#define FIGHT_LABEL_ABILITYDOWN_NUMBER "ui/fight/fight_label_abilitydown_number.png"	//减少的数字
#define FIGHT_LABEL_ABILITYUP_ATTACK "ui/fight/fight_label_abilityup_attack.png"		//攻击力上升
#define FIGHT_LABEL_ABILITYUP_DEFENCE "ui/fight/fight_label_abilityup_defence.png"		//防御力上升
#define FIGHT_LABEL_ABILITYIUP_HP "ui/fight/fight_label_abilityup_hp.png"				//HP增加
#define FIGHT_LABEL_ABILITYUP_BUMBER "ui/fight/fight_label_abilityup_number.png"		//增加的数字
#define FIGHT_LABEL_ACTOR "ui/fight/fight_label_actor.png"								//当前行动者的标记
#define FIGHT_LABEL_LOSE "ui/fight/fight_label_lose.png"								//失败提示文本
#define FIGHT_LABEL_NAME_DIE "ui/fight/fight_label_name_die.png"						//战斗提示信息_死亡
#define FIGHT_LABEL_NAME_DODGE "ui/fight/fight_label_name_dodge.png"					//战斗提示信息_闪避
#define FIGHT_LABEL_NAME_KNOCK "ui/fight/fight_label_name_knock.png"					//战斗提示信息_暴击
#define FIGHT_LABEL_NAME_PARRY "ui/fight/fight_label_name_parry.png"					//战斗提示信息_格挡
#define FIGHT_LABEL_NAME_XXSKILL "ui/fight/fight_label_name_XXskill.png"				//战斗提示信息_XX技能
#define FIGHT_LABEL_ROUND_01 "ui/fight/fight_label_round_01.png"						//战斗提示信息_第
#define FIGHT_LABEL_ROUND_02 "ui/fight/fight_label_round_02.png"						//战斗提示信息_回合
#define FIGHT_LABEL_ROUND_NUMBER "ui/fight/fight_label_round_number.png"				//战斗提示信息_回合数字
#define FIGHT_LABEL_TIMER_1 "ui/fight/fight_label_timer1.png"							//倒计时数字
#define FIGHT_LABEL_TIMER_2 "ui/fight/fight_label_timer2.png"							//倒计时数字
#define FIGHT_LABEL_WIN "ui/fight/fight_label_win.png"									//战斗提示信息_胜利
#define FIGHT_PIC_BTN_CHAT "ui/fight/fight_pic_btn_chat.png"							//聊天按钮
#define FIGHT_PIC_BTN_EXIT_1 "ui/fight/fight_pic_btn_exit_1.png"						//退出按钮1
#define FIGHT_PIC_BTN_EXIT_2 "ui/fight/fight_pic_btn_exit_2.png"						//退出按钮2
#define FIGHT_PIC_CAMP_BLUE "ui/fight/fight_pic_camp_blue.png"							//玩家阵营图标
#define FIGHT_PIC_CAMP_GREEN "ui/fight/fight_pic_camp_green.png"						
#define FIGHT_PIC_CAMP_RED "ui/fight/fight_pic_camp_red.png"							
#define FIGHT_PIC_CAMP_YELLOW "ui/fight/fight_pic_camp_yellow.png"						
#define FIGHT_PIC_ITEM_001 "ui/fight/fight_pic_item001.png"								//道具图标
#define FIGHT_PIC_ITEM_002 "ui/fight/fight_pic_item002.png"								//道具图标
#define FIGHT_PIC_PATHWAY_01 "ui/fight/fight_pic_pathway_01.png"						//轨道辅助线
#define FIGHT_PIC_PATHWAY_02 "ui/fight/fight_pic_pathway_02.png"						//轨道辅助线
#define FIGHT_PIC_PATHWAY_03 "ui/fight/fight_pic_pathway_03.png"						//轨道辅助线
#define FIGHT_PIC_PLAYER_1 "ui/fight/fight_pic_player1.png"								//玩家人物形象
#define FIGHT_PIC_PLAYER_2 "ui/fight/fight_pic_player2.png"									
#define FIGHT_PIC_PLAYER_3 "ui/fight/fight_pic_player3.png"
#define FIGHT_PIC_PLAYER_4 "ui/fight/fight_pic_player4.png"
#define FIGHT_PIC_PLAYERDIE "ui/fight/fight_pic_playerdie.png"							//玩家死亡后的标记
#define FIGHT_PIC_PLAYERHP_BLUE "ui/fight/fight_pic_playerhp_blue.png"					//蓝色血格
#define FIGHT_PIC_PLAYERHP_GREEN "ui/fight/fight_pic_playerhp_green.png"				//绿色血格
#define FIGHT_PIC_PLAYERHP_RED "ui/fight/fight_pic_playerhp_red.png"					//红色血格
#define FIGHT_PIC_PLAYERHP_YELLOW "ui/fight/fight_pic_playerhp_yellow.png"				//黄色血格
#define FIGHT_PIC_PLAYERLEVELNUM "ui/fight/fight_pic_playerlevelnum.png"				//玩家等级数字
#define FIGHT_PIC_PLAYERLV_0 "ui/fight/fight_pic_playerlv0.png"							//玩家等级图标<9
#define FIGHT_PIC_PLAYERLV_1 "ui/fight/fight_pic_playerlv1.png"							//玩家等级图标10-19
#define FIGHT_PIC_PLAYERLV_2 "ui/fight/fight_pic_playerlv2.png"							//玩家等级图标20-29
#define FIGHT_PIC_PLAYERLV_3 "ui/fight/fight_pic_playerlv3.png"							//玩家等级图标30-39
#define FIGHT_PIC_PLAYERLV_4 "ui/fight/fight_pic_playerlv4.png"							//玩家等级图标40-49
#define FIGHT_PIC_PLAYERLV_5 "ui/fight/fight_pic_playerlv5.png"							//玩家等级图标50-59
#define FIGHT_PIC_PLAYERLV_6 "ui/fight/fight_pic_playerlv6.png"							//玩家等级图标60-69
#define FIGHT_PIC_PLAYERLV_7 "ui/fight/fight_pic_playerlv7.png"							//玩家等级图标70-79
#define FIGHT_PIC_PLAYERLV_8 "ui/fight/fight_pic_playerlv8.png"							//玩家等级图标80-89
#define FIGHT_PIC_PLAYERLV_9 "ui/fight/fight_pic_playerlv9.png"							//玩家等级图标90-99
#define FIGHT_PIC_PLAYERLV_10 "ui/fight/fight_pic_playerlv10.png"						//玩家等级图标100
#define FIGHT_PIC_PLAYERMHP "ui/fight/fight_pic_playermhp.png"							//玩家总血槽
#define FIGHT_PIC_SOUL_001 "ui/fight/fight_pic_soul001.png"								//魂魄图标
#define FIGHT_PIC_SOUL_002 "ui/fight/fight_pic_soul002.png"								
#define FIGHT_PIC_TIMER "ui/fight/fight_pic_timer.png"	
#define FIGHT_PIC_BULLET "ui/fight/fight_pic_bullet.png"

#define FIGHT_TILED_MAP_BACKGROUND "ui/fight/MainFightMap.tmx"
//倒计时背景
#endif