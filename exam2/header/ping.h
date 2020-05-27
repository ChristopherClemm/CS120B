
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static unsigned char count = 0;

/*complete the state machine*/

void Ping()
{
	count++;
    switch(ping_state)
    {
        case PInit:
	{
		ping_state = on;
            break;
	}
	case on:
	    {
		ping_state = off;
		break;
	    }
	case off:
	    {
		if(count == 10)
		{
		  count = 0;
		  ping_state = on;
		}
		else
		{
			ping_state = off;
		}
		break;
	    }
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;
	case on:
	{
		pingInfo = 0x01;
		break;
	}
	case off:
	{
		pingInfo = 0x00;
	}
        default:
            break;
    }
}
