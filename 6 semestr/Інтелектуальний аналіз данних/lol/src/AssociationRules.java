/**
 * Created by Katya on 01.05.2017.
 */

import java.io.BufferedReader;
import java.io.FileReader;
//import weka.classifiers.functions.LinearRegression;
//import weka.core.Instance;
import weka.core.Instances;
import weka.associations.Apriori;


public class AssociationRules{
    public static void main(String args[]) throws Exception{
        //load data
        Instances data = new Instances(new BufferedReader(new FileReader("D:/G/breast-cancer.arff")));
        //build model
        Apriori model = new Apriori();
        model.buildAssociations(data);
        System.out.println(model);
    }
}

