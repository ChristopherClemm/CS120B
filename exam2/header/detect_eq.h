//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static unsigned char count1 = 0;

/*complete the state machine*/

void Detect_EQ()
{
	count1++;
    switch(detect_eq_state)
    {
        case DEQInit:
	{
	     detect_eq_state = wait;
            //init variable(s) here.
            break;
	}
	case wait:
	{
		if((~PINA & 0xF8) !=  0x00)
		{
			detect_eq_state = motion_detected;
		}
		else
		{
			detect_eq_state = wait;
		}
		break;
	}
	case motion_detected:
	{
		if(count1 >  10)
	{
			detect_eq_state = wait;
		}
		else
		{
			detect_eq_state = motion_detected;
		}
		break;
	}
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case wait:
	{
		motionData = 0x00;
		break;
	}
	case motion_detected:
	{
		if((~PINA & 0xF8) ==  0x00)
		{
			count1++;
		}
		else
		{
			count1 = 0;
		}
		motionData = 0x02;
		break;
	}

        default:
            break;
    }
}
