template<typename T>
struct test_matrix_multiplier {
	std::vector<std::vector<T>> operator () (std::vector<std::vector<T>>& m1, std::vector<std::vector<T>>& m2) {
		const size_t r = m1.size();
		const size_t c = m2[0].size();
		
		std::vector<std::vector<T>> res(r, std::vector<T>(c, 0));
		
		for(size_t i=0;i<r;i++){
			for(size_t j=0;j<c;j++){
				for(size_t k=0;k<m1[i].size();k++) {
					res[i][j] += m1[i][k] * m2[k][j];
				}
			}
		}
		
		return res;
	}
};

SCENARIO_START

DESCRIBE("Matrix", {
	using namespace nerone;
	
	using TMat = Matrix<int, test_matrix_multiplier<int>>;
	
	TMat* mat;
	
	DESCRIBE("Initialize 3x2 Matrix by cols and rows", {
		BEFORE_EACH({
			mat = new TMat(2,3);
		});
		AFTER_EACH({
			delete mat;
		});
		
		IT("should return 3 when `get_cols` is called", {
			EXPECT(mat->get_cols()).toBe(3);
		});
		
		IT("should return 2 when `get_rows` is called", {
			EXPECT(mat->get_rows()).toBe(2);
		});
		
		DESCRIBE("fill matrix with values: [[1,2,3],[4,5,6]]", {
			BEFORE_EACH({
				for(int i=0;i<2;i++){
					for(int j=0;j<3;j++){
						mat->set(i,j,i*3+j+1);
					}
				}
			});
			
			IT("should return 5 when `get(2,0)` is called", {
				EXPECT(mat->get(1,2)).toBe(6);
			});
			
			DESCRIBE("call `transpose` method", {
				BEFORE_EACH({
					mat->transpose();
				});
				
				IT("should return 2 when `get_cols` is called", {
					EXPECT(mat->get_cols()).toBe(2);
				});
				
				IT("should return 3 when `get_rows` is called", {
					EXPECT(mat->get_rows()).toBe(3);
				});
				
				IT("matrix values should be transposed", {
					for(int i=0;i<2;i++){
						for(int j=0;j<3;j++){
							EXPECT(mat->get(j,i)).toBe(i*3+j+1);
						}
					}
				});
			});
			
			DESCRIBE("Create another matrix from vector<vector<T>>{{7,8},{9,10},{11,12}}", {
				TMat* mat2;
				BEFORE_EACH({
					mat2 = new TMat({{7,8},{9,10},{11,12}});
				});
				
				IT("should return 3 when `mat2.get_rows` is called", {
					EXPECT(mat2->get_rows()).toBe(3);
				});
				
				IT("should return 2 when `mat2.get_cols` is called", {
					EXPECT(mat2->get_cols()).toBe(2);
				});
				
				IT("should return 10 when `mat2.get(1,1)` is called", {
					EXPECT(mat2->get(1,1)).toBe(10);
				});
				
				DESCRIBE("Multiply matrxes", {
					TMat res_mat;
					BEFORE_EACH({
						res_mat = (*mat) * (*mat2);
					});
					
					IT("should return 2 when `res_mat.get_cols` is called", {
						EXPECT(res_mat.get_cols()).toBe(2);
					});
					
					IT("should return 2 when `res_map.get_rows` is called", {
						EXPECT(res_mat.get_rows()).toBe(2);
					});
					
					IT("should contain multiplication of 2 matrixes", {
						vector<vector<int>> expected_res = {{58,64},{139,154}};
						for(int i=0;i<2;i++){
							for(int j=0;j<2;j++){
								EXPECT(res_mat.get(i,j)).toBe(expected_res[i][j]);
							}
						}
					});
					
					IT("should throw if the matrixes are not compatiple for multiplication", {
						mat2->transpose();
						
						EXPECT( ([mat, mat2](){
							(*mat) * (*mat2);
						}) ).toThrowError();
					});
				});
			});
		});
	});
});

SCENARIO_END
