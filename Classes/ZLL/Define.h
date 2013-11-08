#ifndef __MDSJ_ZLL_DEFINE_H__
#define __MDSJ_ZLL_DEFINE_H__


#define DEF_FONT_NAME	"Arial"

#define LAYER_UILAYER_ZINDEX 5		//��������UI��Ĳ��
#define LAYER_POPWINDOW		10

enum ButtomType//��ť����
{
	ButtomType_Red=1,
	ButtomType_Blue1,
	ButtomType_Blue2,
	ButtomType_Blue3,
	ButtomType_Blue4,
	ButtomType_Replace,	//����
};

enum FightType//ս������
{
	FightType_NULL=0,
	FightType_PVP=1,
	FightType_PVE,
	FightType_PVBOSS,
};

enum FightElementNodeType//ս��Ԫ������
{
	FightElementNodeType_Player=1,
	FightElementNodeType_Monster,
};

enum PVEFightType//PVEս������
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

//ͼƬ�ļ��ļ�·��
#define PICPATH_AREMAPATH "ui/Arema/"

//�ظ�����
#define REPEATTEXTURE_1 "ui/repeattexture/repeat_1.png"

//��������Դ
#define ATHLETIC_1V1 "ui/Arema/1v1.png"
#define ATHLETIC_BUTTON_1_1 "ui/Arema/athletic_button1_1.png"	//���ذ�ť
#define ATHLETIC_BUTTON_1_2 "ui/Arema/athletic_button1_2.png"	//���ذ�ť
#define ATHLETIC_BUTTON_1_3 "ui/Arema/athletic_button1_3.png"	//���ذ�ť

#define ATHLETIC_BUTTON_2_1 "ui/Arema/athletic_button2_1.png"	//������Ұ�ť
#define ATHLETIC_BUTTON_2_2 "ui/Arema/athletic_button2_2.png"	//������Ұ�ť
#define ATHLETIC_BUTTON_2_3 "ui/Arema/athletic_button2_3.png"	//������Ұ�ť

#define ATHLETIC_BUTTON_3_1 "ui/Arema/athletic_button3_1.png"	//���ټ��밴ť
#define ATHLETIC_BUTTON_3_2 "ui/Arema/athletic_button3_2.png"	//���ټ��밴ť
#define ATHLETIC_BUTTON_3_3 "ui/Arema/athletic_button3_3.png"	//���ټ��밴ť

#define ATHLETIC_BUTTON_4_1 "ui/Arema/athletic_button4_1.png"	//���߹���ť
#define ATHLETIC_BUTTON_4_2 "ui/Arema/athletic_button4_2.png"	//���߹���ť
#define ATHLETIC_BUTTON_4_3 "ui/Arema/athletic_button4_3.png"	//���߹���ť

#define ATHLETIC_BUTTON_5_1 "ui/Arema/athletic_button5_1.png"	//���Ѱ�ť
#define ATHLETIC_BUTTON_5_2 "ui/Arema/athletic_button5_2.png"	//���Ѱ�ť
#define ATHLETIC_BUTTON_5_3 "ui/Arema/athletic_button5_3.png"	//���Ѱ�ť

#define ATHLETIC_BUTTON_REPLACE_1 "ui/Arema/athletic_replace_1.png"
#define ATHLETIC_BUTTON_REPLACE_2 "ui/Arema/athletic_replace_2.png"
#define ATHLETIC_BUTTON_REPLACE_3 "ui/Arema/athletic_replace_3.png"

#define ATHLETIC_ICON_ITEM_001 "ui/Arema/athletic_icon_item001.png" //����ͼ��
#define ATHLETIC_ICON_MAP_001 "ui/Arema/athletic_icon_map001.png"	//ս����ͼ��ͼ��
#define ATHLETIC_ICON_MAPDIFFICULTY "ui/Arema/athletic_icon_mapdifficulty.png" //��ͼ�Ѷ�ͼ��
#define ATHLETIC_ICON_ROOMLOCK "ui/Arema/athletic_icon_roomlock.png" //����ͼ��
#define ATHLETIC_ICON_SOUL_001 "ui/Arema/athletic_icon_soul001.png" //����ͼ��
#define ATHLETIC_LABEL_PLAYERMESSAGE "ui/Arema/athletic_labe_playermessage.png"	//�����Ϣ��ǩ
#define ATHLETIC_LABEL_ITEM_001 "ui/Arema/athletic_label_item001.png"	//�����ı�����
#define ATHLETIC_LABEL_SOUL_001 "ui/Arema/athletic_label_soul001.png"	//�����ı�����
#define ATHLETIC_LIST_MAP "ui/Arema/athletic_list_map.png" //ս����ͼ�Ĳ˵�ѡ��
#define ATHLETIC_LIST_PLAYER "ui/Arema/athletic_list_player.png" //����б�ѡ��
#define ATHLETIC_LIST_ROOM "ui/Arema/athletic_list_room.png" //����ѡ��˵���
#define ATHLETIC_LIST_TYPE "ui/Arema/athletic_list_type.png" //ģʽѡ��˵���
#define ATHLETIC_PIC_FEMALEPLAYER "ui/Arema/athletic_pic_femaleplayer.png" //Ů���������
#define ATHLETIC_PIC_MALEPLAYER "ui/Arema/athletic_pic_maleplayer.png" //�����������
#define ATHLETIC_SCROORBAR "ui/Arema/athletic_scroorbar.png" //��ֱ������
#define ATHLETIC_TEXTINPUTS_ROOMCODE "ui/Arema/athletic_textinputs_roomcode.png" //����������ı������
#define ATHLETIC_TYPE_ICON_1 "ui/Arema/athletic_type_icon1.png" //����ģʽ��ͼ��
#define ATHLETIC_TYPE_ICON_2 "ui/Arema/athletic_type_icon2.png" //����ģʽ��ͼ��
#define ATHLETIC_TYPE_ICON_3 "ui/Arema/athletic_type_icon3.png" //�Կ�ģʽ��ͼ��
#define ATHLETIC_TYPE_ICON_4 "ui/Arema/athletic_type_icon4.png" //̽��ģʽ��ͼ��
#define ATHLETIC_PROPS_2 "ui/Arema/Props2.png" //����2
#define ATHLETIC_BACKGROUND "ui/Arema/Background.png" //��
#define ATHLETIC_BACKGROUNDSMALL "ui/Arema/BackgroundSmall.png" //��С
#define ATHLETIC_BACKGROUNDSMALL_1 "ui/Arema/BackgroundSmall_1.png" //��С1

#define ATHLETIC_ROOM_ID "ui/Arema/athletic_room_id.png" //����ID
#define ATHLETIC_ROOM_MAP "ui/Arema/athletic_map.png" //��ͼ

#define ATHLETIC_POPWINBACKGROUND_2 "ui/Arema/PopWinBackground2.png"

#define ATHLETIC_TEXTURE "ui/Arema/Texture.png"
#define ATHLETIC_TEXTURE_2 "ui/Arema/Texture2.png"
#define ATHLETIC_PLAYERHEADER "ui/Arema/athletic_playerheader.png"  //���ͷ��

//PVE
#define PVE_FIELD_MAP "ui/PVE/field_map.png"								//Ұ���ͼ
#define PVE_FIELD_PULLDOWNLIST  "ui/PVE/field_pulldownlist.png"				//�����б�
#define PVE_FIELD_BUTTON_MAPNAME  "ui/PVE/field_button_mapname.png"			//��ͼ��
#define PVE_FIELD_BUTTON_MAPNAME_SEL  "ui/PVE/field_button_mapname_sel.png"	//ѡ�еĵ�ͼ��
#define PVE_FIELD_BUTTON_MAPNAME_NOT  "ui/PVE/field_button_mapname_not.png"
#define PVE_FIELD_LABEL_LV  "ui/PVE/field_label_lv.png"						//��ͼ�ȼ��ı�ǩ
#define PVE_FIELD_BUTTON_STAGE  "ui/PVE/field_button_stage.png"				//PVE�ؿ�������ť
#define PVE_FIELD_BUTTON_STAGE_SEL "ui/PVE/field_button_stage_sel.png"			//��ס״̬��PVE�ؿ�������ť
#define PVE_FIELD_PIC_ROAD  "ui/PVE/field_pic_road.png"							//PVE�ؿ�·��ͼ�꣬������ɫ��·��
#define PVE_FIELD_PIC_ROAD_OK  "ui/PVE/field_pic_road_ok.png"				//PVE�ؿ�·��ͼ�꣬��ɫ��·��
#define PVE_FIELD_LABEL_STAGEAME  "ui/PVE/field_label_stagename.png"		//�ؿ������ı�ǩ
#define PVE_FIELD_PIC_STAR_1  "ui/PVE/field_pic_star1.png"					//ս�����۵�����
//#define PVE_FIELD_PIC_STAR_2  "ui/PVE/field_pic_star2.png"					//ս�����۵�����
#define PVE_FIELD_BUTTON_ARROW  "ui/PVE/field_button_arrow.png"				//�����л���ͼ�ļ�ͷ
#define PVE_FIELD_BUTTON_1  "ui/PVE/field_button1.png"						//���ְ�ť
#define PVE_FIELD_BUTTON_1_SEL  "ui/PVE/field_button1_sel.png"				//��ס�ı���ť
#define PVE_FIELD_BUTTON_1_NOT  "ui/PVE/field_button1_not.png"				//��ɫ�ı���ť
#define PVE_FIELD_PIC_STAGEPROMPT  "ui/PVE/field_pic_stageprompt.png"		//�ؿ���ʾͼƬ
#define PVE_FIELD_BGPIC_STAGEMESSAGE  "ui/PVE/field_bgpic_stagemessage.png"	//�ؿ���Ϣ�ı���ͼ
//#define PVE_FIELD_LABEL_1_STAGE  "ui/PVE/field_label_stage.png"				//�ؿ�����Ϣ��ǩ
#define PVE_FIELD_PIC_GROOVE  "ui/PVE/field_pic_groove.png"					//�ؿ�����Ʒ�İ���
#define PVE_FIELD_BUTTON_2  "ui/PVE/field_button2.png"						//���ְ�ť
#define PVE_FIELD_BUTTON_2_SEL  "ui/PVE/field_button2_sel.png"				//��ס���ְ�ť
#define PVE_FIELD_BUTTON_2_NOT  "ui/PVE/field_button2_not.png"					//��ɫ���ְ�ť
#define PVE_FIELD_SCROORBAR  "ui/PVE/field_scroorbar.png"					//��ֱ������
#define PVE_FIELD_BGPIC_HOME  "ui/PVE/field_bgpic_home.png"					//��ӷ���ı���ͼ
#define PVE_FIELD_PIC_STAGE  "ui/PVE/field_pic_stage.png"					//�ؿ�����ͼ
#define PVE_FIELD_PIC_VIPLV  "ui/PVE/field_pic_viplv.png"					//VIP�ȼ�ͼ��
#define PVE_FIELD_BUTTON_SEAT_1  "ui/PVE/field_button_seat1.png"			//�����λ����״̬
#define PVE_FIELD_BUTTON_SEAT_1_SEL  "ui/PVE/field_button_seat1_sel.png"	//��ס����״̬����λ��ť
#define PVE_FIELD_BUTTON_SEAT_2  "ui/PVE/field_button_seat2.png"			//�����λ�ر�״̬
#define PVE_FIELD_BUTTON_SEAT_2_SEL  "ui/PVE/field_button_seat2_sel.png"	//��ס�ر�״̬����λ��ť
#define PVE_FIELD_PIC_RANKSLOCK  "ui/PVE/field_pic_rankslock.png"			//����״̬
#define PVE_FIELD_PIC_ROAD_1  "ui/PVE/field_pic_road1.png"					//�ؿ����·��ʵ��
#define PVE_FIELD_PIC_ROAD_2  "ui/PVE/field_pic_road2.png"					//�ؿ����·������
#define PVE_FIELD_PIC_STAGELOCK  "ui/PVE/field_pic_stagelock.png"			//�ؿ�����ť
#define PVE_FIELD_BUTTON_3  "ui/PVE/field_button3.png"						//���ְ�ť
#define PVE_FIELD_PIC_PLAYER  "ui/PVE/field_pic_player.png"					//�������
#define PVE_FIELD_BUTTON_4  "ui/PVE/field_button4.png"						//���ǵ�����ť
#define PVE_FIELD_BUTTON_4_SEL  "ui/PVE/field_button4_sel.png"				//��ס���ǵ�����ť
#define PVE_FIELD_BUTTON_5  "ui/PVE/field_button5.png"						//���ذ�ť
#define PVE_FIELD_BUTTON_5_SEL  "ui/PVE/field_button5_sel.png"				//���ذ�ť
#define PVE_FIELD_BUTTON_6  "ui/PVE/field_button6.png"						//���밴ť
#define PVE_FIELD_BUTTON_6_SEL  "ui/PVE/field_button6_sel.png"				//���밴ť
#define PVE_FIELD_BGPIC_TEAMNAMETEXT  "ui/PVE/field_bgpic_teamnametext.png"	//�ı������ı���ͼ
#define PVE_FIELD_BGPIC_PLAYERLIST  "ui/PVE/field_bgpic_playerlist.png"		//����б�����
#define PVE_FIELD_BGPIC_PLAYERNAME_WIN  "ui/PVE/field_bgpic_playername_win.png"//ʤ������������ұ���ͼ
#define PVE_FIELD_BGPIC_PLAYERNAME_LOSE  "ui/PVE/field_bgpic_playername_lose.png"//ʧ������������ұ���ͼ
#define PVE_FIELD_BGPIC_WIN  "ui/PVE/fieeld_bgpic_win.png"					//ʤ��̨�ӱ���ͼ
#define PVE_FIELD_BGPIC_LOSE  "ui/PVE/fieeld_bgpic_lose.png"				//ʧ��̨�ӱ���ͼ
#define PVE_FIELD_PIC_MALEPLAYER_1_WIN  "ui/PVE/field_pic_maleplayer1_win.png"//���ʤ��ͼƬ
#define PVE_FIELD_PIC_MALEPLAYER_1_LOSE  "ui/PVE/field_pic_maleplayer1_lose.png"//���ʧ��ͼ��
#define PVE_FIELD_PIC_MALEPLAYER_2_WIN  "ui/PVE/field_pic_maleplayer2_win.png"//���ʤ��ͼƬ
#define PVE_FIELD_PIC_MALEPLAYER_2_LOSE  "ui/PVE/field_pic_maleplayer2_lose.png"//���ʧ��ͼ��
#define PVE_FIELD_PIC_FEMALEPLAYER_1_WIN  "ui/PVE/field_pic_femaleplayer1_win.png"//���ʤ��ͼƬ
#define PVE_FIELD_PIC_FEMALEPLAYER_1_LOSE  "ui/PVE/field_pic_femaleplayer1_lose.png"//���ʧ��ͼ��
#define PVE_FIELD_PIC_FEMALEPLAYER_2_WIN  "ui/PVE/field_pic_femaleplayer2_win.png"//���ʤ��ͼƬ
#define PVE_FIELD_PIC_FEMALEPLAYER_2_LOSE  "ui/PVE/field_pic_femaleplayer2_lose.png"//���ʧ��ͼ��
#define PVE_FIELD_BGPIC_BATTLEEND  "ui/PVE/fiel_bgpic_battleend.png"		//ս���������ͼ
#define PVE_FIELD_CARD_FRONT  "ui/PVE/field_card_front.png"					//ս������Ŀ�������
#define PVE_FIELD_CARD_BACK  "ui/PVE/field_card_back.png"	
#define PVE_FIELD_FIELD_SEARCHTEAM_INPUTID  "ui/PVE/field_searchteam_inputId.png"
#define PVE_FIELD_POPWIN_BACKGROUND "ui/PVE/field_popwin_background.png"
#define PVE_FIELD_GAMEROOM_READY  "ui/PVE/field_gameroom_ready.png"
#define PVE_FIELD_GAMEROOM_MASTER  "ui/PVE/field_gameroom_master.png"
#define PVE_FIELD_BUTTON_MAPNAME_1  "ui/PVE/field_button_mapname1.png"
//ս������Ŀ��Ʊ���

//ս����Դ
#define FIGHT_BGPIC_ITEMSOUL "ui/fight/fight_bgpic_itemsoul.png"						//���ߺͻ��ǵ�ͼ�갼��
#define FIGHT_BGPIC_LEAVE "ui/fight/fight_bgpic_leave.png"								//�˳�2��ȷ�Ͽ�ı���
#define FIGHT_BGPIC_MAP "ui/fight/fight_bgpic_map.png"										//ս������ͼ,�����ƻ��ĵ���
#define FIGHT_BGPIC_BACKGROUND "ui/fight/fight_pic_background.png"						//ս������
#define FIGHT_BGPIC_PLAYERORDER "ui/fight/fight_bgpic_playerorder.png"					//����ж�˳����Ϣ����ͼ
#define FIGHT_LABEL_ABILITYDOWN_ATTACK "ui/fight/fight_label_abilitydown_attack.png"	//�������½���ǩ
#define FIGHT_LABEL_ABILITYDOWN_DEFENCE "ui/fight/fight_label_abilitydown_defence.png"	//�������½���ǩ
#define FIGHT_LABEL_ABILITYDOWN_HP "ui/fight/fight_label_abilitydown_hp.png"			//HP���ٱ�ǩ
#define FIGHT_LABEL_ABILITYDOWN_NUMBER "ui/fight/fight_label_abilitydown_number.png"	//���ٵ�����
#define FIGHT_LABEL_ABILITYUP_ATTACK "ui/fight/fight_label_abilityup_attack.png"		//����������
#define FIGHT_LABEL_ABILITYUP_DEFENCE "ui/fight/fight_label_abilityup_defence.png"		//����������
#define FIGHT_LABEL_ABILITYIUP_HP "ui/fight/fight_label_abilityup_hp.png"				//HP����
#define FIGHT_LABEL_ABILITYUP_BUMBER "ui/fight/fight_label_abilityup_number.png"		//���ӵ�����
#define FIGHT_LABEL_ACTOR "ui/fight/fight_label_actor.png"								//��ǰ�ж��ߵı��
#define FIGHT_LABEL_LOSE "ui/fight/fight_label_lose.png"								//ʧ����ʾ�ı�
#define FIGHT_LABEL_NAME_DIE "ui/fight/fight_label_name_die.png"						//ս����ʾ��Ϣ_����
#define FIGHT_LABEL_NAME_DODGE "ui/fight/fight_label_name_dodge.png"					//ս����ʾ��Ϣ_����
#define FIGHT_LABEL_NAME_KNOCK "ui/fight/fight_label_name_knock.png"					//ս����ʾ��Ϣ_����
#define FIGHT_LABEL_NAME_PARRY "ui/fight/fight_label_name_parry.png"					//ս����ʾ��Ϣ_��
#define FIGHT_LABEL_NAME_XXSKILL "ui/fight/fight_label_name_XXskill.png"				//ս����ʾ��Ϣ_XX����
#define FIGHT_LABEL_ROUND_01 "ui/fight/fight_label_round_01.png"						//ս����ʾ��Ϣ_��
#define FIGHT_LABEL_ROUND_02 "ui/fight/fight_label_round_02.png"						//ս����ʾ��Ϣ_�غ�
#define FIGHT_LABEL_ROUND_NUMBER "ui/fight/fight_label_round_number.png"				//ս����ʾ��Ϣ_�غ�����
#define FIGHT_LABEL_TIMER_1 "ui/fight/fight_label_timer1.png"							//����ʱ����
#define FIGHT_LABEL_TIMER_2 "ui/fight/fight_label_timer2.png"							//����ʱ����
#define FIGHT_LABEL_WIN "ui/fight/fight_label_win.png"									//ս����ʾ��Ϣ_ʤ��
#define FIGHT_PIC_BTN_CHAT "ui/fight/fight_pic_btn_chat.png"							//���찴ť
#define FIGHT_PIC_BTN_EXIT_1 "ui/fight/fight_pic_btn_exit_1.png"						//�˳���ť1
#define FIGHT_PIC_BTN_EXIT_2 "ui/fight/fight_pic_btn_exit_2.png"						//�˳���ť2
#define FIGHT_PIC_CAMP_BLUE "ui/fight/fight_pic_camp_blue.png"							//�����Ӫͼ��
#define FIGHT_PIC_CAMP_GREEN "ui/fight/fight_pic_camp_green.png"						
#define FIGHT_PIC_CAMP_RED "ui/fight/fight_pic_camp_red.png"							
#define FIGHT_PIC_CAMP_YELLOW "ui/fight/fight_pic_camp_yellow.png"						
#define FIGHT_PIC_ITEM_001 "ui/fight/fight_pic_item001.png"								//����ͼ��
#define FIGHT_PIC_ITEM_002 "ui/fight/fight_pic_item002.png"								//����ͼ��
#define FIGHT_PIC_PATHWAY_01 "ui/fight/fight_pic_pathway_01.png"						//���������
#define FIGHT_PIC_PATHWAY_02 "ui/fight/fight_pic_pathway_02.png"						//���������
#define FIGHT_PIC_PATHWAY_03 "ui/fight/fight_pic_pathway_03.png"						//���������
#define FIGHT_PIC_PLAYER_1 "ui/fight/fight_pic_player1.png"								//�����������
#define FIGHT_PIC_PLAYER_2 "ui/fight/fight_pic_player2.png"									
#define FIGHT_PIC_PLAYER_3 "ui/fight/fight_pic_player3.png"
#define FIGHT_PIC_PLAYER_4 "ui/fight/fight_pic_player4.png"
#define FIGHT_PIC_PLAYERDIE "ui/fight/fight_pic_playerdie.png"							//���������ı��
#define FIGHT_PIC_PLAYERHP_BLUE "ui/fight/fight_pic_playerhp_blue.png"					//��ɫѪ��
#define FIGHT_PIC_PLAYERHP_GREEN "ui/fight/fight_pic_playerhp_green.png"				//��ɫѪ��
#define FIGHT_PIC_PLAYERHP_RED "ui/fight/fight_pic_playerhp_red.png"					//��ɫѪ��
#define FIGHT_PIC_PLAYERHP_YELLOW "ui/fight/fight_pic_playerhp_yellow.png"				//��ɫѪ��
#define FIGHT_PIC_PLAYERLEVELNUM "ui/fight/fight_pic_playerlevelnum.png"				//��ҵȼ�����
#define FIGHT_PIC_PLAYERLV_0 "ui/fight/fight_pic_playerlv0.png"							//��ҵȼ�ͼ��<9
#define FIGHT_PIC_PLAYERLV_1 "ui/fight/fight_pic_playerlv1.png"							//��ҵȼ�ͼ��10-19
#define FIGHT_PIC_PLAYERLV_2 "ui/fight/fight_pic_playerlv2.png"							//��ҵȼ�ͼ��20-29
#define FIGHT_PIC_PLAYERLV_3 "ui/fight/fight_pic_playerlv3.png"							//��ҵȼ�ͼ��30-39
#define FIGHT_PIC_PLAYERLV_4 "ui/fight/fight_pic_playerlv4.png"							//��ҵȼ�ͼ��40-49
#define FIGHT_PIC_PLAYERLV_5 "ui/fight/fight_pic_playerlv5.png"							//��ҵȼ�ͼ��50-59
#define FIGHT_PIC_PLAYERLV_6 "ui/fight/fight_pic_playerlv6.png"							//��ҵȼ�ͼ��60-69
#define FIGHT_PIC_PLAYERLV_7 "ui/fight/fight_pic_playerlv7.png"							//��ҵȼ�ͼ��70-79
#define FIGHT_PIC_PLAYERLV_8 "ui/fight/fight_pic_playerlv8.png"							//��ҵȼ�ͼ��80-89
#define FIGHT_PIC_PLAYERLV_9 "ui/fight/fight_pic_playerlv9.png"							//��ҵȼ�ͼ��90-99
#define FIGHT_PIC_PLAYERLV_10 "ui/fight/fight_pic_playerlv10.png"						//��ҵȼ�ͼ��100
#define FIGHT_PIC_PLAYERMHP "ui/fight/fight_pic_playermhp.png"							//�����Ѫ��
#define FIGHT_PIC_SOUL_001 "ui/fight/fight_pic_soul001.png"								//����ͼ��
#define FIGHT_PIC_SOUL_002 "ui/fight/fight_pic_soul002.png"								
#define FIGHT_PIC_TIMER "ui/fight/fight_pic_timer.png"	
#define FIGHT_PIC_BULLET "ui/fight/fight_pic_bullet.png"

#define FIGHT_TILED_MAP_BACKGROUND "ui/fight/MainFightMap.tmx"
//����ʱ����
#endif