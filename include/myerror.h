/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** myerror
*/

#ifndef MYERROR_H_
    #define MYERROR_H_

#define err(condition, err_desc, retval)\
        if ((condition) == 1) {         \
            printf("%s\n", err_desc);   \
            return retval;              \
        }                               \

#define perr(condition, err_desc, retval)\
        if ((condition) == 1) {          \
            perror(err_desc);            \
            return retval;               \
        }                                \

#endif /* !MYERROR_H_ */
