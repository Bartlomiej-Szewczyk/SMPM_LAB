#include "GFX_FUNCTIONS.h"
#include "ST7735.h"
/*zmienne z innych części programu */

/* z silnika : */
#define start_angle 		//kat startowy silnika 
#define current_angle		// aktualne położenie silnika
#define predicted_angle		// docelowe położenie silnika



void Start_Screen (uint16_t gesture)
{
	
	
	hagl_fill_rectangle(1,1,50,30, YELLOW);
	hagl_fill_rectangle(1,129,50,159, YELLOW);
	hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
	hagl_fill_rectangle(77,129,77+50,129+30, YELLOW);
	hagl_put_text(u"Ster silnikiem",2,2, BLACK, font5x7);
	hagl_put_text(u"predkosc katowa",2,130, BLACK, font5x7);
	hagl_put_text(u"Info",78,2, BLACK, font5x7);
	hagl_put_text(u"Euler",78,130, BLACK, font5x7);

	switch (gesture)
	{
	case 1
	hagl_fill_rectangle(1,1,50,30, CYAN);
	hagl_putPtext(u"Ster silnikiem",2,2, RED, font5x7);
	
	Screen_Motor_Steering();
	
	case 2
	hagl_fill_rectangle(1,129,50,159, CYAN);
	hagl_putPtext(u"predkosc katowa",2,130, RED, font5x7);
	
	
	case 3
	hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
	hagl_putPtext(u"Info",78,2, RED, font5x7);
	
	
	case 4
	hagl_fill_rectangle(77,129,77+50,30+129, CYAN);
	hagl_put_text(u"Euler",78,130, RED, font5x7);
	}
}


/* Menu wyboru trybu sterowania silnikiem */
void Screen_Motor_Steering( uint16_t gesture_2)
{
	int pos_x0 = 29;
	int width = 70;
	int height = 15;
	
	hagl_fill_rounded_rectangle(pos_x0,140,pos_x0 + width, 140 + height, 3, YELLOW);
	hagl_put_text("TRYB 0", pos_x0 + 5, 145, RED, font6x9);
	hagl_fill_rounded_rectangle( pos_x0, 120, pos_x0 + width, 120 + height, 3, YELLOW );
	hagl_put_text("TRYB 1", pos_x0 + 5, 125, RED, font6x9);
	
	hagl_put_text("Opis trybu 0", 5, 100, BLACK, font5x7);
	hagl_put_text("Opis trybu 1", 5, 50, BLACK, font5x7);
	
	switch(gesture_2)
	{
		case 1:
		hagl_fill_rounded_rectangle(pos_x0,140,pos_x0 + width, 140 + height, 3, CYAN);
		hagl_put_text("TRYB 0", pos_x0 + 5, 145, RED, font6x9);
		
		GoTo_0_mode();
		
		case 2:
		hagl_fill_rounded_rectangle( pos_x0, 120, pos_x0 + width, 120 + height, 3, CYAN);
		hagl_put_text("TRYB 1", pos_x0 + 5, 125, RED, font6x9);
		
		GoTo_1_mode();
	}
}
/*kąty wybierane za pomocą gestu obracania palcem */
/* panel trybu 0 pracy silnika - poruszanie sie z kierunku a na kierunek B */
void GoTo_0_mode ( )
{
	/* Menu trybu 0 */
	hagl_fill_rectangle(1,1,50,30, CYAN);
	hagl_putPtext(u"Tryb 0",2,2, BLACK, font6x9);

	hagl_fill_rectangle(1,129,50,159, YELLOW);
	hagl_fill_rectangle(77,1,77+50,30+1, YELLOW);
	hagl_fill_rectangle(77,129,77+50,129+30, YELLOW);
	
	hagl_put_text(u"Kat startowy",2,130, BLACK, font5x7);
	hagl_put_text(u"Powrot",78,2, BLACK, font5x7);
	hagl_put_text(u"Kat obrot",78,130, BLACK, font5x7);
	
		switch (gesture)
	{
		
	case 2
	hagl_fill_rectangle(1,129,50,159, CYAN);
	hagl_putPtext(u"Kat startowy",2,130, RED, font5x7);
	
	/*zadanie kąta początkowego */
	GoTo_Start_angle_screen();
	
	
	case 3
	hagl_fill_rectangle(77,1,77+50,30+1, CYAN);
	hagl_putPtext(u"Powrot",78,2, RED, font5x7);
	 
	Screen_Motor_Steering();
	
	case 4
	hagl_fill_rectangle(77,129,77+50,30+129, CYAN);
	hagl_put_text(u"Kat obrot",78,130, RED, font5x7);
	
	/* ekran do nastawienia kąta obrotu silnika */
	GoTo_rotate_angle_settings();		
	}
	
}

/* panel trybu 1 - nadążanie na kierunek A */
void GoTo_1_mode()
{
	
}


/* funkcja wyświetlająca "animowany potencjometr" 
 gesture_rot_direction - informacja o kierunku obrotu palcem - 1 prawo, 2 - lewo, 0 - brak wykrycia ruchu */
 
void potentiometer_animation(int gesture_rot_direction, uint16_t Screen_Height, uint16_t Screen_Width)
{
	/* Współrzędne obszaru wyświetlania animacji potencjometru */
	uint16_t pot_area = 50;
	uint16_t x0_pot_area = (Screen_Width - pot_area)/2;
	uint16_t y0_pot_area = (Screen_Height - pot_area)/2;
	uint16_t x1_pot_area = (Screen_Width + pot_area)/2;
	uint16_t y1_pot_area = (Screen_Height + pot_area)/2;
	uint16_t x_c = Screen_Width/2;
	uint16_t y_c = Screen_Height/2;
	/* tablice z punktami na okręgu o promieniu 25 */
	uint16_t x_tab[24] = {0,5,13,18,22,24,25,24,22,18,13,5,0,-5,-13,-18,-22,-24,-25,-24,-22,-18,-13,-5};
	uint16_t y_tab[24] = {25,24,22,18,13,5,0,-5,-13,-18,-22,-24,-25,-24,-22,-18,-13,-5,0,5,13,18,22,24};
	/* okno do łatwego wyświetlania i usuwania obrazu */ 
	hagl_set_clip_window(x0_pot_area, y0_pot_area, x1_pot_area, y1_pot_area );
	/*trzeba mi tu rozrysować kolo o promieniu r w którym będzie mniejsze kółko w innym kolorze obracać się zgodnie/przeciwnie do ruchu wskazówek zegara */
	hagl_fill_circle(x_c,y_c, 25, MAGENTA);
	hagl_draw_vline(x_c,y_c,24,YELLOW);
	
	if(gesture_rot_direction = 1)	// obrót w prawo
	{
	/* narysowanie linii prostej zmieniającej położenie z każdą iteracją */ 
		for(int i =0; i <24; i++)
		{
			hgl_clear_clip_window();
			hagl_fill_circle(x_c,y_c, 25, MAGENTA);
			int x1 = x_c + x_tab[i];
			int y1 = y_c + y_tab [i];
			hagl_draw_line(x_c,y_c, x1, y1, YELLOW);
		}
	}
	/* obrót przeciwnie do ruchu wskazówek zegara */
	if(gesture_rot_direction = 2)
	{
		for(int i = 24; i > 0; i--)
		{
		hgl_clear_clip_window();
		hagl_fill_circle(x_c,y_c, 25, MAGENTA);
		int x1 = x_c + x_tab[i];
		int y1 = y_c + y_tab [i];
		hagl_draw_line(x_c,y_c, x1, y1, YELLOW);
		}
	}
	
}
void Angle_menu (const wchar_t *Title, uint16_t current_angle, const wchar_t *Mode )
{
	hagl_fill_rectangle(1,1,30,30, CYAN);
	/* wyświetlanie trybu w lewym dolnym rogu */
	hagl_put_text(*Mode, 2, 2, BLACK, font6x9);
	
	/* wyświetlanie aktualnej wartości kąta na dole na środku ekranu */ 
	hagl_fill_rounded_rectangle(20, 35, 40, 93, 3, CYAN;
	hagl_put_text(current_angle, 22, 37, YELLOW, font6x9);
	potentiometer_animation( gesture_rot_direction, 160, 128);
	
	
	/* powrót pod wpływem dotknięcia prawego dolnego rogu Flicka */ 
	
	if(gesture == 3)
	{
		if( Mode == "Tryb 0")
		{
			GoTo_0_mode();
		}
		if (Mode == "Tryb 1")
		{
			GoTo_1_mode();
		}
	}
}