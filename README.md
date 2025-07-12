# Project Tyrant

---

## Language - ENG

Project Tyrant is an atmospheric single-player game made on Unreal Engine 5.5 with a focus on stealth mechanics, advanced dynamic monster AI and a frightening sonic atmosphere. The project is fully implemented in C++ with no blueprint code.

[Gameplay video](https://youtu.be/KbksC_SMxkE)

## 🎮 Gameplay Features

- The main goal of the player: to activate 6 scanners scattered around the map. Once all scanners are activated, a large gate opens, allowing the player to escape the level and win the game.
- Monster with advanced AI implemented in State Trees and C++:
  - Chasing: if the monster sees the player, it immediately starts chasing the player.
  - Losing the player: if the player hides out of sight, the monster goes to the last place it saw him.
  - Reaction to Noise: the monster reacts to noise created by the player by running and activating scanners. It heads towards the last source of noise.
  - Search: if the monster can't see or hear the player, it starts searching through predetermined points:
    - It chooses the closest point based on the distance of the path, taking obstacles into account.
    - At the beginning of the search, it prefers points in the direction of its movement (based on the last known direction of the player), even if other points are closer.
    - Remembers which points it has already checked so that it does not return to them again. The list is reset to zero if:
      - The monster's behavior changes (e.g., it sees the player again).
      - All points have been checked, but the player is still not found (then the search starts again).
  - Attack: If the monster catches up with the player and stays near the player for a certain amount of time (less than one second), a kill screen is triggered (the player still has a chance to escape if not cornered).
  - Difficulty Levels:
    - *Easy:* monster does not react to running, only to scanners.
    - *Normal:* the behavior described above.
    - *Difficult:* the monster always knows where the player is.
- When the scanner is activated, it has an animation playing

## 🎵 Sounds and Music

- Dynamic Music:

  - The game features two player pursuit music tracks, randomly selected when the music starts.
  - Each song consists of:
    - An intro.
    - A looped middle.
    - An ending.
  - Transitions between parts are smooth and customizable in the editor.
  - The music starts when the monster enters chase mode or when it goes to the last known position of the player.
  - As soon as the monster loses sight and sound of the player and starts actively searching, there is a transition to the end of the track.
  - Upon victory or defeat, the music is momentarily interrupted.

- Additional sound effects:

  - The scanner activation sound is loud, attracting the monster's attention.
  - Separate sounds for winning and losing screens.
  - Player and monster movement sounds.
  - Sound of opening the gate - loud, attracting the attention of the player.

- There is music in the main menu and pause menu.

## 🧭 User Interface and Menus

- Main Menu:
  - Game start, settings and exit buttons.
- Game start menu:
  - Difficulty level selection and back button.
- Settings Menu:
  - Tabs for graphics and sound settings, and a back button;
  - In graphics: screen resolution, windowed/full-screen/full-screen-in-window modes, VSync, many picture quality settings (texture and model quality, etc.).
  - In sound: volume of music, effects and general sound.
  - All settings are saved in an .ini file.
- Pause Menu:
  - Pauses the game and sounds.
  - Options: continue, open settings or exit to main menu.

## 🛠 Technical Details

- Engine: Unreal Engine 5.5
- Language: C++ (no Blueprint code)
- Player movement: based on Mover 2.0
- Monster AI: implemented entirely through State Trees and State Tree Tasks in C++
- Code: clean, flexible and documented

## 📇 Developer contacts

**Vladislav Semchuk**\
*(also known as Vladyslav Semchuk or Driver2579)*\
[LinkedIn](https://www.linkedin.com/in/vladislav-semchuk-a2b944203/)

---

## Language - UA

Project Tyrant - це атмосферна однокористувацька гра, виконана на Unreal Engine 5.5, з фокусом на стелс-механіках, просунутому динамічному штучному інтелекті монстра і лякаючою звуковою атмосферою. Проєкт повністю реалізований на C++ без використання блюпринт-коду.

[Геймплей відео](https://youtu.be/KbksC_SMxkE)

## 🎮 Особливості геймплею

- Головна мета гравця: активувати 6 сканерів, розкиданих по карті. Після активації всіх сканерів відчиняються великі ворота, що дають змогу гравцеві втекти з рівня і виграти гру.
- Монстр із просунутим штучним інтелектом, реалізованим на State Trees і C++:
  - Переслідування: якщо монстр бачить гравця, він негайно починає його переслідувати.
  - Втрата гравця: якщо гравець ховається з поля зору, монстр іде до останнього місця, де він його бачив.
  - Реакція на шум: монстр реагує на шум, створюваний гравцем - біг і активація сканерів. Він прямує до останнього джерела шуму.
  - Пошук: якщо монстр не бачить і не чує гравця, він починає пошук за заздалегідь заданими точками:
    - Вибирає найближчу точку за відстанню шляху з урахуванням перешкод.
    - На початку пошуку віддає перевагу точкам, розташованим у напрямку його руху (орієнтуючись за останнім відомим напрямком гравця), навіть якщо інші точки ближче.
    - Запам'ятовує, які точки він уже перевірив, щоб не повертатися в них повторно. Список обнуляється, якщо:
      - Поведінка монстра змінюється (наприклад, він знову бачить гравця).
      - Усі точки було перевірено, але гравця так і не знайдено (тоді пошук починається заново).
  - Атака: якщо монстр наздоганяє гравця і перебуває поруч протягом певного часу (менше однієї секунди), спрацьовує екран ураження (у гравця залишається шанс втекти, якщо його не загнали в кут).
  - Рівні складності:
    - *Легкий:* монстр не реагує на біг, тільки на сканери.
    - *Нормальний:* поведінка, описана вище.
    - *Складний:* монстр завжди знає, де знаходиться гравець.
- При активації сканера, у нього програється анімація

## 🎵 Звуки та музика

- Динамічна музика:

  - У грі дві музичні композиції переслідування гравця, що випадково обираються при старті музики.
  - Кожна композиція складається з:
    - Вступу.
    - Зацикленої середини.
    - Кінцівки.
  - Переходи між частинами - плавні та налаштовуються в редакторі.
  - Музика стартує під час переходу монстра в режим погоні або коли він іде до останньої відомої позиції гравця.
  - Щойно монстр втрачає гравця з поля зору і звуку та починає активний пошук, відбувається перехід до кінцівки треку.
  - У разі перемоги або поразки музика миттєво переривається.

- Додаткові звукові ефекти:

  - Звук активації сканерів - гучний, що привертає увагу монстра.
  - Окремі звуки для екранів виграшу і програшу.
  - Звуки пересування гравця і монстра.
  - Звук відкриття воріт - гучний, що привертає увагу гравця.

- Є музика в головному меню і меню паузи.

## 🧭 Інтерфейс і меню

- Головне меню:
  - Кнопки початку гри, налаштувань і виходу.
- Меню початку гри:
  - Вибір рівня складності та кнопка повернення назад.
- Меню налаштувань:
  - Вкладки налаштувань графіки і звуку, і кнопка повернення назад;
  - У графіці доступні: роздільна здатність екрана, режими віконний/повноекранний/повноекранний у вікні, VSync, безліч налаштувань якості картинки (якість текстур і моделей та ін.).
  - У звуці: гучність музики, ефектів і загального звуку.
  - Усі налаштування зберігаються в .ini файл.
- Меню паузи:
  - Призупиняє гру і звуки.
  - Опції: продовжити, відкрити налаштування або вийти в головне меню.

## 🛠 Технічні деталі

- Рушій: Unreal Engine 5.5
- Мова: C++ (без блюпринт-коду)
- Переміщення гравця: засноване на Mover 2.0
- ШІ монстра: реалізовано повністю через State Trees і State Tree Tasks на C++
- Код: чистий, гнучкий і документований

## 📇 Контакти розробника

**Владислав Семчук**\
*(також відомий як Driver2579)*\
[LinkedIn](https://www.linkedin.com/in/vladislav-semchuk-a2b944203/)

---

## Language - RU

Project Tyrant — это атмосферная однопользовательская игра, выполненная на Unreal Engine 5.5, с фокусом на стелс-механиках, продвинутом динамическом ИИ монстра и пугающей звуковой атмосферой. Проект полностью реализован на C++ без использования блюпринт-кода.

[Геймплей видео](https://youtu.be/KbksC_SMxkE)

## 🎮 Особенности геймплея

- Главная цель игрока: активировать 6 сканеров, разбросанных по карте. После активации всех сканеров открываются большие ворота, позволяющие игроку сбежать с уровня и выиграть игру.
- Монстр с продвинутым ИИ, реализованным на State Trees и C++:
  - Преследование: если монстр видит игрока, он немедленно начинает его преследовать.
  - Потеря игрока: если игрок скрывается из поля зрения, монстр идет к последнему месту, где он его видел.
  - Реакция на шум: монстр реагирует на шум, создаваемый игроком — бег и активация сканеров. Он направляется к последнему источнику шума.
  - Поиск: если монстр не видит и не слышит игрока, он начинает поиск по заранее заданным точкам:
    - Выбирает ближайшую точку по расстоянию пути с учетом препятствий.
    - В начале поиска предпочитает точки, находящиеся в направлении его движения (ориентируясь по последнему известному направлению игрока), даже если другие точки ближе.
    - Запоминает, какие точки он уже проверил, чтобы не возвращаться в них повторно. Список обнуляется, если:
      - Поведение монстра меняется (например, он снова видит игрока).
      - Все точки были проверены, но игрок так и не найден (тогда поиск начинается заново).
  - Атака: если монстр догоняет игрока и находится рядом в течении определенного времени (меньше одной секунды), срабатывает экран поражения (у игрока остается шанс убежать, если его не загнали в угол).
  - Уровни сложности:
    - *Легкий:* монстр не реагирует на бег, только на сканеры.
    - *Нормальный:* поведение, описанное выше.
    - *Сложный:* монстр всегда знает, где находится игрок.
- При активации сканера, у него проигрывается анимация

## 🎵 Звуки и музыка

- Динамическая музыка:

  - В игре две музыкальные композиции преследования игрока, случайно выбираемые при старте музыки.
  - Каждая композиция состоит из:
    - Вступления.
    - Зацикленной середины.
    - Концовки.
  - Переходы между частями — плавные и настраиваются в редакторе.
  - Музыка стартует при переходе монстра в режим погони или когда он идет к последней известной позиции игрока.
  - Как только монстр теряет игрока из виду и звука и начинает активный поиск, происходит переход к концовке трека.
  - При победе или поражении музыка мгновенно прерывается.

- Дополнительные звуковые эффекты:

  - Звук активации сканеров — громкий, привлекающий внимание монстра.
  - Отдельные звуки для экранов выигрыша и проигрыша.
  - Звуки передвижения игрока и монстра.
  - Звук открытия ворот — громкий, превлекающий внимание игрока.

- Имеется музыка в главном меню и меню паузы.

## 🧭 Интерфейс и меню

- Главное меню:
  - Кнопки начала игры, настроек и выхода.
- Меню начала игры:
  - Выбор уровня сложности и кнопка возврата назад.
- Меню настроек:
  - Вкладки настроек графики и звука, и кнопка возврата назад;
  - В графике доступны: разрешение экрана, режимы оконный/полноэкранный/полноэкранный в окне, VSync, множество настроек качества картинки (качество текстур и моделей и др.).
  - В звуке: громкость музыки, эффектов и общего звука.
  - Все настройки сохраняются в .ini файл.
- Меню паузы:
  - Приостанавливает игру и звуки.
  - Опции: продолжить, открыть настройки или выйти в главное меню.

## 🛠 Технические детали

- Движок: Unreal Engine 5.5
- Язык: C++ (без блюпринт-кода)
- Перемещение игрока: основано на Mover 2.0
- ИИ монстра: реализован полностью через State Trees и State Tree Tasks на C++
- Код: чистый, гибкий и документированный

## 📇 Контакты разработчика

**Владислав Семчук**\
*(также известный как Driver2579)*\
[LinkedIn](https://www.linkedin.com/in/vladislav-semchuk-a2b944203/)
