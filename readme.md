# CoreWar 42

## TO-DO List:
- [X] Написать TO-DO list
- [X] Champion      (easy)          :boom:
- [X] Validator     (medium)        :boom::boom:
    - [X] Считывать только 1 аргумент
    - [X] Проверка имени
        - [X] Имя идет после `NAME_CMD_STRING`
        - [X] Длина строки не больше `PROG_NAME_LENGTH`
        - [X] Проверка на содержание
            - [X] Имя не может отсутствовать
    - [X] Проверка комментария
        - [X] Комментарий идет после `COMMENT_CMD_STRING`
        - [X] Длина строки не больше `PROG_CMD_LENGTH`
        - [X] Проверка на содержание
            - [X] Коммент не может отсутствовать
    - [X] Проверка метки
        - [X] Метка должна состоять только из `LABEL_CHARS`
        - [?] Если метку передают как аргумент, то она обязана быть в коде
                                                как указатель на инструкцию
        - [X] Может быть несколько одинаковых меток на одну и ту же инструкцию
        - [X] Может быть несколько одинаковых меток на разные инструкции
    - [X] Проверка аргументов:
        - [X] Аргументы разделяются только с помощью `SEPARATOR_CHAR`
        - [X] `+` не может быть в начале аргумента
        - [X] T_REG состоит из буквы `r` и числа из одной или двух цифр
            - [X] `r0` и `r00` всегда невалидные
            - [X] Перед однозначным числом может стоять `0`
        - [X] Если в аргументе указывается метка, то она должна быть в коде
                                            как указатель на инструкции
- [X] Asm           (medium)        :boom::boom::boom:
- [X] Vm            (Done)