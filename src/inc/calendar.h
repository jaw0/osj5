

/* number of centuries since 1700, not inclusive */
#define centuries_since_1700(yr) \
        ((yr) > 1700 ? (yr) / 100 - 17 : 0)
 
/* number of centuries since 1700 whose modulo of 400 is 0 */
#define quad_centuries_since_1700(yr) \
        ((yr) > 1600 ? ((yr) - 1600) / 400 : 0)
 
/* number of leap years between year 1 and this year, not inclusive */
#define leap_years_since_year_1(yr) \
        ((yr) / 4 - centuries_since_1700(yr) + quad_centuries_since_1700(yr))

/* leap year -- account for gregorian reformation in 1752 */
#define leap_year(yr) \
        ((yr) <= 1752 ? !((yr) % 4) : \
        !((yr) % 4) && ((yr) % 100) || !((yr) % 400))
