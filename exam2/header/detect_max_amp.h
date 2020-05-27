
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char tempMax = 0x00;
/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
	{
	    detect_max_amp_state = wait2;
            break;
	}
	case wait2:
	{
		if(motionData == 0x02)
		{
			detect_max_amp_state = findMax;

		}
		else
		{
			detect_max_amp_state = wait2;
		}
		break;
	}
	case findMax:
	{
		if (motionData == 0x02)
		{
			detect_max_amp_state = findMax;
		}
		else
		{
			detect_max_amp_state = wait2;
		}
		break;
	}
        
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	case wait2:
	    {
		max = 0x00;
		break;
	    }
	case findMax:
	    {	
		tempMax =(~PINA & 0xF8);
		if (tempMax > max)
		{
			max = tempMax;
		}
		else
		{
			max = max;
		}

		break;


	    }
        default:
            break;
    }
}
