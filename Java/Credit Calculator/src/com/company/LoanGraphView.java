package com.company;

import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.VBox;

import java.util.ArrayList;

public class LoanGraphView extends LoanView{
    private XYChart.Series series;
    LineChart lineChart;
    private NumberAxis xAxis;
    private NumberAxis yAxis;

    public LoanGraphView(){
        super();

        //Defining the x axis
        xAxis = new NumberAxis();
        xAxis.setLabel("Mėnuo");

        //Defining the y axis
        yAxis = new NumberAxis();
        yAxis.setLabel("Mokėti");

        lineChart = new LineChart(xAxis, yAxis);

        series = new XYChart.Series();
        series.setName("Paskolos grąžinimo grafikas");

        root.getChildren().addAll(lineChart);
    }

    @Override
    public void fillData(ArrayList<PaymentData> monthlyPayment){
        yAxis.setUpperBound(monthlyPayment.get(0).getMonthlyAmount());
        xAxis.setUpperBound(monthlyPayment.size());

        yAxis.setTickUnit(monthlyPayment.get(0).getLeftAmount());
        xAxis.setTickUnit(1);

        monthlyPayment.forEach((n) -> {
            series.getData().add(new XYChart.Data(n.getId(), n.getMonthlyAmount()));
        });

        lineChart.getData().add(series);
    }
}
