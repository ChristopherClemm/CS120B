
void PlayGame()
{
	switch(gamestate)
	{
		case GAMEINIT:
		{

			gamestate = PLAY;
			break;
		}
		case PLAY:
		{
		 	gamestate = PLAY;
			break;

		}
		case OVER:
		{
			gamestate = OVER;
			break;
		}
		default:
		{
			gamestate = PLAY;
			break;
		}

	}
	switch(gamestate)
        {
                case GAMEINIT:
                {

                       
                        break;
                }
                case PLAY:
                {
           

                        break;

                }
                case OVER:
                {
                      
                        break;
                }
                default:
                {
                        gamestate = PLAY;
                        break;
                }

        }


}
