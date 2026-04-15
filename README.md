# Программа для отслеживания изменений файлов в реальном времени. Позволяет добавлять файлы в список наблюдения и получать уведомления об изменениях их состояния.
Функциональные возможности

Добавление файлов в наблюдение - файл добавляется даже если физически отсутствует (будет отслеживаться его появление)
Удаление файлов из наблюдения - файл перестает отслеживаться
Просмотр списка наблюдаемых файлов - отображает все файлы с их текущим статусом
Автоматическое отслеживание изменений - программа проверяет файлы каждые 100 мс
Уведомления об изменениях: появление нового файла, исчезновение файла, изменение размера файла

<img width="1863" height="1001" alt="Снимок экрана 2026-04-14 141134" src="https://github.com/user-attachments/assets/03c7f2b8-4257-46e7-b335-3ff658a98020" />

Тестирование
Commands:
add <path>

remove <path>

list

exit

add file.txt

File added: file.txt size: 243

add m.txt

File added: m.txt size: 2

add i.txt

File added (waiting for appearance): i.txt

add p.txt

File added (waiting for appearance): p.txt

remove p.txt

file deleted from monitoring: p.txt

list

1. file.txt - exists, size 243
   
2. m.txt - exists, size 2
   
3. i.txt - missing
   
exit
