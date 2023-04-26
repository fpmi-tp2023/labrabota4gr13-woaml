#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>

enum menu{
    SELECT = 0,
    INSERT = 1,
    DELETE = 2,
    WHERE = 3,
    BEGIN = 4,
    COMMIT = 5 
};

enum columns{
    ID = 0,
    NAME = 1,
    AMOUNT = 2,
    NETPRICE = 3,
    GROSSPRICE = 4,
    PRODUCTIONDATE = 5,
    MANUFACTURER= 6,
    PHONENUMBER = 7,
    ADDRESS = 8,
    SHOP_ID = 9
};

char *commands[] = {
    "SELECT * from Product", "INSERT INTO Product VALUES(", "DELETE FROM Product",
    " WHERE ", "BEGIN TRANSACTION; ", "; COMMIT;"
};

char *col[] = {
    "id", "name", "amount", "netPrice", "grossPrice", "productionDate", "manufacturer", "phoneNumber", "address", "shop_id"
};

#endif
