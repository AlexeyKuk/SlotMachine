
/*
*				SlotMachine
*/

bin:
	Win - SlotMachine_Win32.exe
	Debian - SlotMachine_x64
	
Для запуска необходимо наличие папки pic и файла config.xml в папке с исполняемым файлом


Некоторые XML параметры:
	- изменение количества барабанов (COUNT_WHEELS)
	- изменение количества слотов в барабане (COUNT_SLOTS)
	// необходимао, чтобы количество барабанов было не более чем кол-во значения для
	// параметров : WHEEL_DELAYED, WHEEL_SLOWING, WHEEL_SPEED (изначально их задано 10)
	
	- рамеры окна можно изменить с помощью (SCENE_HORIZ_MIN/SCENE_HORIZ_MAX по горизонтали, и VERT по вертикали)
	- изменение размеров картинок (SLOT_WIDTH/SLOT_HEIGHT)
	- изменение расстояния между барабанами (OFFSET_WHEEL)
	- изменение расстояния между слотами (OFFSET_SLOT)
	
	- изменение fps (INITIAL_FPS)