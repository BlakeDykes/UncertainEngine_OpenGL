#include "ControlMap_ChickenBot_Default.h"
#include "PlayerController.h"

namespace Uncertain
{
	void ControlMap_ChickenBot_Default::HandleAction(Keyboard::Key key, PlayerController& playerController)
	{
		Command* pCom;

		switch (key)
		{
		case Keyboard::KEY_SPACE:

			break;

		case Keyboard::KEY_APOSTROPHE:
			break;
		case Keyboard::KEY_COMMA:
			break;
		case Keyboard::KEY_MINUS:
			break;
		case Keyboard::KEY_PERIOD:
			break;
		case Keyboard::KEY_SLASH:
			break;

		case Keyboard::KEY_0:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_WALK, true);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_1:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_RUN, true);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_2:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_SHOT_F, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_3:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_SHOT_D, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_4:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_SHOT_U, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_5:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_HIT_F, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_6:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_HIT_L, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_7:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_HIT_R, false);
			CommandQueueManager::SendData(pCom);
			break;
		case Keyboard::KEY_8:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_SIDESTEP_L, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_9:
			pCom = new CMD_SetAnim(*playerController.GetAnimController(), AnimName::S_CHICKENBOT_SIDESTEP_R, false);
			CommandQueueManager::SendData(pCom);
			break;

		case Keyboard::KEY_SEMICOLON:
			break;
		case Keyboard::KEY_EQUAL:
			break;
		case Keyboard::KEY_A:
			break;
		case Keyboard::KEY_B:
			break;
		case Keyboard::KEY_C:
			break;
		case Keyboard::KEY_D:
			break;
		case Keyboard::KEY_E:
			break;
		case Keyboard::KEY_F:
			break;
		case Keyboard::KEY_G:
			break;
		case Keyboard::KEY_H:
			break;
		case Keyboard::KEY_I:
			break;
		case Keyboard::KEY_J:
			break;
		case Keyboard::KEY_K:
			break;
		case Keyboard::KEY_L:
			break;
		case Keyboard::KEY_M:
			break;
		case Keyboard::KEY_N:
			break;
		case Keyboard::KEY_O:
			break;
		case Keyboard::KEY_P:
			break;
		case Keyboard::KEY_Q:
			break;
		case Keyboard::KEY_R:
			break;
		case Keyboard::KEY_S:
			break;
		case Keyboard::KEY_T:
			break;
		case Keyboard::KEY_U:
			break;
		case Keyboard::KEY_V:
			break;
		case Keyboard::KEY_W:
			break;
		case Keyboard::KEY_X:
			break;
		case Keyboard::KEY_Y:
			break;
		case Keyboard::KEY_Z:
			break;
		case Keyboard::KEY_LEFT_BRACKET:
			break;
		case Keyboard::KEY_BACKSLASH:
			break;
		case Keyboard::KEY_RIGHT_BRACKET:
			break;
		case Keyboard::KEY_GRAVE_ACCENT:
			break;
		case Keyboard::KEY_ARROW_UP:
			break;
		case Keyboard::KEY_ARROW_DOWN:
			break;
		case Keyboard::KEY_ARROW_LEFT:
			break;
		case Keyboard::KEY_ARROW_RIGHT:
			break;
		case Keyboard::KEY_ESCAPE:
			break;
		case Keyboard::KEY_ENTER:
			break;
		case Keyboard::KEY_TAB:
			break;
		case Keyboard::KEY_BACKSPACE:
			break;
		case Keyboard::KEY_INSERT:
			break;
		case Keyboard::KEY_DELETE:
			break;

		case Keyboard::KEY_LEFT_SHIFT:
		case Keyboard::KEY_LEFT_CONTROL:
		case Keyboard::KEY_LEFT_ALT:
		case Keyboard::KEY_RIGHT_SHIFT:
		case Keyboard::KEY_RIGHT_CONTROL:
		case Keyboard::KEY_RIGHT_ALT:
		case Keyboard::SIZE:
		case Keyboard::UNINITIALIZED:
		default:
			break;
		}
	}
}
