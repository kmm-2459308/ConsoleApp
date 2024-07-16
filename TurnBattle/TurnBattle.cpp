//======================================
//	�^�[�����o�g��
//======================================
#include "TurnBattle.h"
#include "Utility.h"
#include <stdio.h>  // printf()

// �֐��v���g�^�C�v
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense);

// �^�[���o�g���ݒ�
void SetTurnBattle(TurnBattle* btl, Character* player, Character* enemy , Character* yaranaio, Character* yaruo)
{
	btl->player = player;
	btl->enemy = enemy;
	btl->yaruo = yaruo;
	//btl->yaranaio = yaranaio;
}
// �C���g���u�`�����ꂽ!!�v�\��
void IntroTurnBattle(TurnBattle* btl)
{
	DrawBattleScreen(btl);
	// �������Łu(�G�̖��O)���@�����ꂽ!!�v��\�����Ă�������
	//printf("%s���@�����ꂽ!!\n", btl->enemy->name);
	printf("%s���@�����ꂽ!!\n", btl->yaruo->name);
	//printf("%s���@�����ꂽ!!\n", btl->yaranaio->name);
	WaitKey();
}
// �o�g���J�n
void StartTurnBattle(TurnBattle* btl)
{
	btl->turn = 1;
	StartCharacter(btl->player);
	//StartCharacter(btl->enemy);
	StartCharacter(btl->yaruo);
	//StartCharacter(btl->yaranaio);
}
// �o�g����ʂ�`��
void DrawBattleScreen(TurnBattle* btl)
{
	ClearScreen();
	IndicatePlayer(btl->player);
	putchar('\n');
	//IndicateEnemy(btl->enemy);
	//putchar('\n');
	IndicateEnemy(btl->yaruo);
	putchar('\n');
	//IndicateEnemy(btl->yaranaio);
	//putchar('\n');
}
// �v���[���̃^�[�����s
/*bool ExecPlayerTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->player, btl->enemy);
	if (IsDeadCharacter(btl->enemy)) {
		SetEraseAa(btl->enemy);
		DrawBattleScreen(btl);
		// �������Łu(�G�̖��O)���@��������!�v��\�����Ă�������
		printf("%s�����������I\n", btl->enemy->name);
		WaitKey();
		return true;
	}
	return IsEscapeCharacter(btl->player);
}*/
bool ExecPlayerTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->player, btl->yaruo);
	if (IsDeadCharacter(btl->yaruo)) {
		SetEraseAa(btl->yaruo);
		DrawBattleScreen(btl);
		// �������Łu(�G�̖��O)���@��������!�v��\�����Ă�������
		printf("%s�����������I\n", btl->yaruo->name);
		WaitKey();
		return true;
	}

	/*execCommand(btl, cmd, btl->player, btl->yaranaio);
	if (IsDeadCharacter(btl->yaranaio)) {
		SetEraseAa(btl->yaranaio);
		DrawBattleScreen(btl);
		// �������Łu(�G�̖��O)���@��������!�v��\�����Ă�������
		printf("%s�����������I\n", btl->yaranaio->name);
		WaitKey();
		return true;
	}*/
	return IsEscapeCharacter(btl->player);
}
// �G�̃^�[�����s
/*bool ExecEnemyTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->enemy, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		// �������Łu"���Ȃ��́@���ɂ܂����v��\�����Ă�������
		printf("���Ȃ��́@���ɂ܂���\n");
		WaitKey();
		return true;
	}
	return false;
}*/

bool ExecEnemyTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->yaruo, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		// �������Łu"���Ȃ��́@���ɂ܂����v��\�����Ă�������
		printf("���Ȃ��́@���ɂ܂���\n");
		WaitKey();
		return true;
	}
	/*execCommand(btl, cmd, btl->yaranaio, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		// �������Łu"���Ȃ��́@���ɂ܂����v��\�����Ă�������
		printf("���Ȃ��́@���ɂ܂���\n");
		WaitKey();
		return true;
	}*/
	return false;
}
// �R�}���h���s(offense:�U���L���� defense:�h��L����)
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense)
{
	int dmg;
	switch (cmd) {
	case COMMAND_FIGHT:
		DrawBattleScreen(btl);
		// �������Łu(�U�����̖��O)�́@��������!�v��\�����Ă�������
		printf("%s�̂��������I\n", offense->name);
		WaitKey();

		dmg = CalcDamage(offense);
		DamageCharacter(defense, dmg);
		DrawBattleScreen(btl);
		// �������Łu(�h�䑤�̖��O)�� (�_���[�W�l)�́@�_���[�W!�v��\�����Ă�������
		printf("%s��%d�̃_���[�W�I\n", defense->name, dmg);
		WaitKey();

		break;
	case COMMAND_SPELL:
		if (CanSpellCharacter(offense) == false) {
			DrawBattleScreen(btl);
			// �������Łu�l�o���@����Ȃ�!�v��\�����Ă�������
			printf("MP������Ȃ��I\n");
			WaitKey();
			break;
		}
		UseSpellCharacter(offense);
		DrawBattleScreen(btl);
		// �������Łu(�U�����̖��O)�́@�q�[�����@�ƂȂ���!�v��\�����Ă�������
		printf("%s�̓q�[�����ƂȂ����I\n", offense->name);
		WaitKey();

		RecoverCharacter(offense);
		DrawBattleScreen(btl);
		// �������Łu(�U�����̖��O)�̂������@�����ӂ�����!�v��\�����Ă�������
		printf("%s�̂������@�����ӂ������I\n", offense->name);
		WaitKey();
		break;

	case COMMAND_ESCAPE:
		DrawBattleScreen(btl);
		// �������Łu(�U�����̖��O)�́@�ɂ�������!�v��\�����Ă�������
		printf("%s�́@�ɂ��������I\n", offense->name);
		WaitKey();
		SetEscapeCharacter(offense);
		break;
	}
}
// ���̃^�[����
void NextTurnBattle(TurnBattle* btl)
{
	btl->turn++;
}