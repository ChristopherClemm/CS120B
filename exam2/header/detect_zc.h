
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static unsigned char tempStore = 0x00;
static unsigned char curr = 0x00;

/*complete the state machine*/

void Detect_ZC()
{
    switch(detect_zc_state)
    {
        case DZCInit:
	{
		detect_zc_state = wait3;
	    	break;
	}
	case wait3:
	{
		if(motionData == 0x02)
		{
			detect_zc_state = checkSwitch;
		}
		else
		{
			detect_zc_state = wait3;
		}
		break;
	}
	case checkSwitch:
	{
		if(motionData == 0x00)
		{
			detect_zc_state = wait3;
		}
		else
		{
			detect_zc_state = checkSwitch;
		}
		break;
	}
        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit:
            break;
	case wait3:
	    {
		zc = 0x00;
		break;
	    }
	case checkSwitch:
	    {

		
			curr = (~PINA & 0x07);


			if((curr + 0x04) == tempStore)
			{
				zc = 0x04;
			}
			else if (( curr - 0x04) == tempStore)
			{
				zc = 0x04;
			}
			else
			{
				zc = 0x00;
			}
			tempStore = curr;
		
		break;
	    }
        default:
            break;
    }
}
