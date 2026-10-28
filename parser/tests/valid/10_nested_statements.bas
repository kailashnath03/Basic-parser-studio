FOR ROW = 1 TO 3
    FOR COL = 1 TO 3
        IF ROW = COL THEN
            PRINT "Diagonal: "; ROW; COL
        ELSE
            PRINT "Other: "; ROW; COL
        END IF
    NEXT COL
NEXT ROW

