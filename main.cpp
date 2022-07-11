#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOBJ.h>
#include <igl/png/readPNG.h>
#include <igl/png/writePNG.h>
#include <iostream>


//   V  double matrix of vertex positions  #V by 3
//   TC  double matrix of texture coordinats #TC by 2
//   N  double matrix of corner normals #N by 3
//   F  #F list of face indices into vertex positions
//   FTC  #F list of face indices into vertex texture coordinates
//   FN  #F list of face indices into vertex normals
Eigen::MatrixXd V;
Eigen::MatrixXd TC;
Eigen::MatrixXd N;
Eigen::MatrixXi F;
Eigen::MatrixXi FTC;
Eigen::MatrixXi FN;

bool key_down(igl::opengl::glfw::Viewer& viewer, unsigned char key, int modifier)
{
	if (key == '1')
	{
		// Allocate temporary buffers
		Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R(1280, 800);
		Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> G(1280, 800);
		Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> B(1280, 800);
		Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> A(1280, 800);

		// Draw the scene in the buffers
		viewer.core().draw_buffer(
			viewer.data(), false, R, G, B, A);

		// Save it to a PNG
		igl::png::writePNG(R, G, B, A, "./Resources/out.png");
	}
	return false;
}

int main(int argc, char* argv[])
{

	//igl::read_triangle_mesh("./Resources/t1.obj", V, F);
	igl::readOBJ("./Resources/t1.obj", V, TC, N, F, FTC, FN);
	Eigen::Matrix<unsigned char, Eigen::Dynamic, Eigen::Dynamic> R, G, B, A;
	igl::png::readPNG("./Resources/t1_low.png", R, G, B, A);


	// Plot the mesh
	igl::opengl::glfw::Viewer viewer;
	viewer.callback_key_down = &key_down;
	viewer.data().set_mesh(V, F);
	viewer.data().set_uv(TC, FTC);
	viewer.data().set_texture(R, G, B, A);
	viewer.data().show_lines = false;
	viewer.data().show_texture = true;
	viewer.core().orthographic = true;
	// Launch the viewer
	viewer.launch();
}
