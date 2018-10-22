package edu.dhbw.mannheim.tigers.sumatra.model.modules.impls.botmanager.bots.grsim;

public class TransformMatrix
{
	private int				columns;
	private int				rows;
	private double[][]	data;
	
	
	public double[][] getData()
	{
		return data;
	}
	
	
	public TransformMatrix(final int r, final int c, final double d[])
	{
		rows = r;
		columns = c;
		data = new double[rows][columns];
		for (int i = 0, k = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++, k++)
			{
				data[i][j] = d[k];
			}
		}
	}
	
	
	public TransformMatrix(final int r, final int c, final double d[][])
	{
		rows = r;
		columns = c;
		data = new double[rows][columns];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				data[i][j] = d[i][j];
			}
		}
	}
	
	
	public void print()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				System.out.print(data[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	
	public TransformMatrix multiplication(final TransformMatrix m)
	{
		double[][] data = new double[rows][m.columns];
		if (columns == m.rows)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < m.columns; j++)
				{
					for (int k = 0; k < columns; k++)
					{
						data[i][j] += this.data[i][k] * m.data[k][j];
					}
				}
			}
		}
		else
		{
			System.out.println("this.columns != m.rows");
		}
		TransformMatrix r = new TransformMatrix(rows, m.columns, data);
		return r;
	}
	
	
	public TransformMatrix inverse()
	{
		double[][] identity = new double[][] { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
		double[] d = new double[3];
		double[] di = new double[3];
		double c;
		boolean inversible = true;
		
		if (rows != columns)
		{
			inversible = false;
		}
		if (inversible)
		{
			// metodo de gauss-jordan
			// transforma triagular
			for (int k = 0; (k < (columns - 1)) && inversible; k++)
			{
				for (int i = 1; (i < (rows - k)) && inversible; i++)
				{
					if (data[k][k] != 0)
					{
						// c = fator que vai multiplicar cada linha
						c = -data[i + k][k] / data[k][k];
						// cout<<"c="<<c<<" data1="<<data[i+k][k]<<" data="<<data[k][k]<<endl;
						// prepara linha pra somar com a debaixo
						for (int j = 0; j < columns; j++)
						{
							d[j] = data[k][j] * c;
							data[i + k][j] += d[j];
							
							di[j] = identity[k][j] * c;
							identity[i + k][j] += di[j];
						}
						// cout<<d[0]<<d[1]<<d[2]<<endl;
						// print();
					}
					else
					{
						inversible = false;
					}
				}
			}
			for (int k = columns - 1; (k > 0) && inversible; k--)
			{
				for (int i = 1; (i <= k) && inversible; i++)
				{
					if (data[k][k] != 0)
					{
						c = -data[k - i][k] / data[k][k];
						// cout<<"c="<<c<<" data1="<<data[k-i][k]<<" data="<<data[k][k]<<endl;
						for (int j = 0; j < columns; j++)
						{
							d[j] = data[k][j] * c;
							// cout<<"data[k-1][j]="<<data[k-i][j]<<" d[j]="<<d[j]<<endl;
							// cout<<"calc="<<roundf(data[k-i][j]+d[j])<<endl;
							data[k - i][j] = data[k - i][j] + d[j];
							di[j] = identity[k][j] * c;
							identity[k - i][j] = identity[k - i][j] + di[j];
						}
						// cout<<d[0]<<d[1]<<d[2]<<endl;
						// print();
					}
					else
					{
						inversible = false;
					}
				}
			}
			for (int i = 0; (i < rows) && inversible; i++)
			{
				c = data[i][i];
				// cout<<"c="<<c<<endl;
				for (int j = 0; (j < columns) && inversible; j++)
				{
					identity[i][j] /= c;
				}
				// print();
			}
			/*
			 * for(int i = 0; i < rows; i++){
			 * for(int j = 0; j < columns; j++){
			 * cout << identidade[i][j] << " ";
			 * }
			 * printf("\n");
			 * }
			 */
		}
		else
		{
			System.out.println("Matriz não é inversível\n");
		}
		TransformMatrix r = new TransformMatrix(3, 3, identity);
		return r;
	}
}
