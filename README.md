## Task
Determine the list of winning countries in the Dopobachenia-2020 competition. The name of the directory in which all .csv text files must be read is given to the input. All such files in the folder with examples and your version have the following format `Country, number of votes in country №1-№20`, for example:
```csv
1
Ukraine,78000,6156,495,7,9456460,45645,21213,898...
```
The first line contains the number of countries in each of the files. Each subsequent line contains the number of votes from each of the participating countries. In the example above, Ukraine received 78,000 votes from country #1, 6,156 votes from country #2, and so on. The country with the highest number of votes (in a column) receives 12 points, the second place - 10, from the third to the tenth - 8-1 points, respectively. It is necessary to calculate the total number of points for each country and display the top 10 winners in a text file.

#### Input and output data
The name of the folder is given to the input of the program. The output is a results.csv file with the results of the top ten countries Dopobachenia-2020. The output should contain a single execution result for all files in the input directory.
