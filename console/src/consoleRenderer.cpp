#include "consoleRenderer.h"
#include <algorithm>


void ConsoleRenderer::beginScene(const Camera& camera)
{
	m_camera = camera;
	// Clear frame buffer
	memset(m_frameBuffer, m_clearChar, m_frameBufferSize - 1);
}
void ConsoleRenderer::submit(const ConsoleMaterial & mat)
{
	int srcLeftIdx, srcRightIdx;
	int dstLeftIdx, dstRightIdx;

	if(mat.right() < m_camera.left()) return; // Material is to the left camera 
	if(mat.left() > m_camera.right()) return; // Material is to the right camera
	if(mat.bottom() < m_camera.top()) return; // Material is above camera
	if(mat.top() > m_camera.bottom()) return; // Material is below camera

	// Left idx
	if (mat.left() < m_camera.left()) // Material intersects on the left of camera
	{
		srcLeftIdx = m_camera.left() - mat.left();
		dstLeftIdx = 0;
	}
	else // Material left is inside the camera
	{
		srcLeftIdx = 0;
		dstLeftIdx = mat.left() - m_camera.left();
	}

	// Right idx
	if (mat.right() < m_camera.right()) // Material right is inside the camera
	{
		srcRightIdx = mat.width();
		dstRightIdx = dstLeftIdx - srcLeftIdx + mat.width();
	}
	else // Material right intersects on the right side of camera
	{
		srcRightIdx = m_camera.width() - (dstLeftIdx -srcLeftIdx);
		dstRightIdx = m_camera.width();
	}


	int srcTopIdx, srcBottomIdx;
	int dstTopIdx, dstBottomIdx;

	// Top idx
	if (mat.top() < m_camera.top()) // Material intersects on the top of camera
	{
		srcTopIdx = m_camera.top() - mat.top();
		dstTopIdx = 0;
	}
	else // Material left is inside the camera
	{
		srcTopIdx = 0;
		dstTopIdx = mat.top() - m_camera.top();
	}

	// Bottom idx
	if (mat.bottom() < m_camera.bottom()) // Material right is inside the camera
	{
		srcBottomIdx = mat.height();
		dstBottomIdx = dstTopIdx - srcTopIdx + mat.height();
	}
	else // Material right intersects on the right side of camera
	{
		srcBottomIdx = m_camera.height() - (dstTopIdx - srcTopIdx);
		dstBottomIdx = m_camera.height();
	}

	char * matData = mat.data();
	for (int i = srcLeftIdx, j = dstLeftIdx; i < srcRightIdx; i++, j++)
	{
		for (int k = srcTopIdx, l = dstTopIdx; k < srcBottomIdx; k++, l++)
		{
			m_frameBuffer[j + l * m_consoleWidth] = matData[i + k * mat.width()];
		}
	}

}

void ConsoleRenderer::endScene()
{
	m_frameBuffer[m_frameBufferSize - 1] = '\0';
}

void ConsoleRenderer::flush()
{
	// Render framebuffer
	printf("\n%s", m_frameBuffer);
}

void ConsoleRenderer::setClearChar(char ch)
{
	m_clearChar = ch;
}
