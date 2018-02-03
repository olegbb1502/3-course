package com.company;

import java.awt.*;

/**
 * Created by Наталья on 3/10/2016.
 */
public class City extends Point {
    public int order;
    public static int radius = 10;

    public City(int x, int y, int order) {
        this.x = x;
        this.y = y;
        this.order = order;
    }

    public City(City city) {
        this.order = city.order;
        this.x = city.x;
        this.y = city.y;
    }

    public boolean equals(City city) {
        if((x==city.x)&&(y==city.y)) {
            return true;
        }
        return false;
    }

    public void setOrder(int order) {
        this.order = order;
    }
}
