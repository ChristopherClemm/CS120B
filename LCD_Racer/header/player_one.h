void PlayerOne()
{
	switch(player_one_state)
	{
		case PLAYER_ONE_INIT:
		{
			 player_one_state = PLAYER_ONE_STAY;
			 break;

		}
		case PLAYER_ONE_STAY:
		{

			if(play == 0x01)
			{
		
				if((~PINA & 0x01) == 0x01)
				{	
					if(player_one_cursor < 16)
					{
						player_one_state = PLAYER_ONE_DOWN;

					}	
					else
					{
						player_one_state = PLAYER_ONE_UP;
					}

				}
				
			}
			else
			{
				player_one_state = PLAYER_ONE_DEAD;
			}
			break;


		}
		case PLAYER_ONE_DOWN:
		{

			player_one_state = PLAYER_ONE_WAIT;
			break;
		}
		case PLAYER_ONE_UP:
		{
			player_one_state = PLAYER_ONE_WAIT;
			break;
		}
		case PLAYER_ONE_WAIT:
		{
			if((~PINA & 0x01) == 0x01)
			{
				player_one_state = PLAYER_ONE_WAIT;
			}
			else
			{
				player_one_state = PLAYER_ONE_STAY;
			}
			break;

		}
		case PLAYER_ONE_DEAD:
		{
			if(play == 0x00)
			{
				player_one_state = PLAYER_ONE_DEAD;
			}
			else
			{
				player_one_state = PLAYER_ONE_STAY;
			}
			break;
		}
	
	}

	switch(player_one_state)
	{
		case PLAYER_ONE_INIT:
		{
			player_one_cursor = 1;
                        LCD_Cursor(player_one_cursor);
                        LCD_WriteData('%');
			break;
		}
		case PLAYER_ONE_WAIT:
		{
			break;
		}
		case PLAYER_ONE_UP:
		{
			LCD_Cursor(player_one_cursor);
			LCD_WriteData(' ');
			
			player_one_cursor -=16;
			LCD_Cursor(player_one_cursor);
			LCD_WriteData('%');
			break;
		}
		case PLAYER_ONE_DOWN:
		{

			LCD_Cursor(player_one_cursor);
			LCD_WriteData(' ');
                      
			player_one_cursor +=16;
                        LCD_Cursor(player_one_cursor);
                        LCD_WriteData('%');
			break;
		}
		case PLAYER_ONE_DEAD:
		{
			break;
		}
		case PLAYER_ONE_STAY:
		{
			LCD_Cursor(player_one_cursor);
			LCD_WriteData('%');

			break;
		}


	}

}
