#include "gameLayer.h"
#include <map>

GameLayer::GameLayer()
{
	m_world = new b2World(b2Vec2(0.f, 9.81f));

	m_renderer.setClearChar(' ');
	m_camera = Camera(0,0,120,30);

	m_labels.resize(2);

	char ch[15] = {
		'X','X','X','X','X',
		'X','X',char(206),'X','X',
		'X','X','X','X','X' };
	


	m_labels[0] = Label(glm::vec2(10.f, 5.f), GameObject::invView(5, 3), 15, ch);
	m_labels[1] = Label(glm::vec2(3.3f, 1.65f),  GameObject::invView(3,3), 15, "___===---");
	

	m_animation = Drawable(glm::vec2(10.f, 5.f), GameObject::invView(6,5), 30, "        ''  o_()_o  /\\   d  b ");
	m_SmallBomb = Drawable(glm::vec2(2.f, 3.f), GameObject::invView(24, 12), 288, "                                                                                 *   *                 *  * *  *            *    **#**    *           *   * *   *            *   *   *   *              *     *                                                                                 ");
	m_LargeBomb = Drawable(glm::vec2(6.f, 0.5f), GameObject::invView(48, 24), 1152, "");
	m_sBombUI = Drawable(glm::vec2(1.f, 0.5f), GameObject::invView(7, 2), 14, "   ,     (*)  ");
	m_lBombUI = Drawable(glm::vec2(2.f, 0.5f), GameObject::invView(7, 2), 14, "  -,    ( X ) ");
	//m_rocketUI = Drawable(glm::vec2(6.f, 0.5f), GameObject::invView(48, 24), 1152, "");


	std::map<unsigned int, char> specialChars;
	specialChars[2] = char(201);
	specialChars[3] = char(187);
	m_animation.addFrame("  XX    ''  o_()_o  /\\   d  b ", specialChars);
	m_animation.addFrame("  XX    ''  o_()_o  /\\   d  b ", specialChars);
	m_animation.addFrame("  XX    ''  o_()_o  /\\   d  b ", specialChars);
	m_animation.addFrame("  XX    ''  o_()_o  /\\   d  b ", specialChars);
	m_animation.addFrame("  XX    ''  o_()_o  /L   d  b ", specialChars);
	m_animation.addFrame("  XX    ''  o_()_o  /L   d  b ", specialChars);
	m_animation.addFrame("  XX    ''  o_()_o  /L   d  b ", specialChars);
	m_animation.addFrame("  XX  o ''   \\()_o  /l   d b  ", specialChars);
	m_animation.addFrame("  XX  o ''   \\()_o  /l   d b  ", specialChars);
	m_animation.addFrame("  XX  o ''   \\()_o  /l   d b  ", specialChars);
	m_animation.addFrame("  XX  o ''   \\()_o  /l   d b  ", specialChars);
	m_animation.addFrame("  XX  o ''   \\()_o  /l   d b  ", specialChars);

	// Small Bomb animation //
	m_SmallBomb.addFrame("                                                                                 *   *                 *  * *  *            *    **#**    *           *   * *   *            *   *   *   *              *     *                                                                                 ",3);
	m_SmallBomb.addFrame("                            *   *      *   *      *   *          *   *     *   (        )    *      *   *(   )*   *     *      ( (*#*) )       **  *(    (###)    )*  *    *  (  (*#*)  )  *     *   *  *(   )*  *   *     *    *     *    *        * *          * *         *   *   *   *              ",3);
	m_SmallBomb.addFrame("*   *      *      *    *       *  * *  *             *  *     *  *         *    (  *  )    *        *   *(   )*   *     *      (  (*)  )       *  *  *(  ( # )  )*  *       *  (  (*)  )  *      *   *  *(   )*  *   *     *    (  *  )    *         *  *     *  *             *  * *  *        ",3);
	m_SmallBomb.addFrame("                                                         *   *                  *#* *#*                  *#*#*                    *#*                    *#*#*                  *#* *#*                *#*   *#*                *     *                                                         ",3);
	m_SmallBomb.addFrame("                                                                                 #   #                    # #                      #                      # #                    #   #                                                                                                          ",3);
	m_SmallBomb.addFrame("                                                                                 *   *                    * *                      *                      * *                    *   *                                                                                                          ",3);
	m_SmallBomb.addFrame("                                                                                                                                   *                                                                                                                                                            ",3);
	
	// Large Bomb animation //
	m_LargeBomb.addFrame("  **           **         **            **          ****   ****             ****    ****              *******                 *******                   *****                 *****                      *****               *****                         ****             ****                              ***         ***                                    **  *  **                                    ***  *****  ***                                    ***(*)***                                      *  *   *  *                                     * ( #*# ) *                                  ( * ( ( # ) ) * )                                 *(   *#*   )*                                     * *#*#* *                                        *******                                        ***   ***                                      ****   ****                                 *******     *******                          *********       *********                      ********           ********                   **********           **********                **        **         **        **             **           **       **          **         ",3);
	m_LargeBomb.addFrame(" *#*        **               **        *#*          *##*   *##*             *##*   *##*              *#######*               *#######*                *######*               *######*                  *######*             *######*                    *#####*             *#####*                      *#####*           *#####*                        *#####*         *#####*                           *###*         *###*                              **##**     **##**                                 *##**   **##*                                    *#* #*# *#*                                     (*( *#* )*)                                       (**#**)                                        * *#*#* *                                       *#######*                                      *###* *###                                     *####*  *####*                               *#######*  *########*                         *#######*      *########*                      *########*      *#########*                  *##########*       *###########*               *##########*         *###########*            **###########*         *############**       ",3);
	m_LargeBomb.addFrame(" ####      ####             ####      ####         ###########               ###########             ########                 #########               #######                 ########                 #######               ########                   #######             #######                      #######           #######                        #######         #######                          #######       #######                             ######     ######                                 #####   #####                                    ###########                                       #######                                         #######                                        #########                                      ###########                                    ###### ######                                 #######   #######                             ########     ########                         #########       #########                      ##########       ##########                   ###########         ###########                ############         ############             ###############       ###############        ",3);
	m_LargeBomb.addFrame(" ****      ****             ****      ****         ***********               ***********             ********                 *********               *******                 ********                 *******               ********                   *******             *******                      *******           *******                        *******         *******                          *******       *******                             ******     ******                                 *****   *****                                    ***********                                       *******                                         *******                                        *********                                      ***********                                    ****** ******                                 *******   *******                             ********     ********                         *********       *********                      **********       **********                   ***********         ***********                ************         ************             ***************       ***************        ",3);
	m_LargeBomb.addFrame("                                                     *******                   *******                 ****                     ****                    ***                     ***                      ***                   ***                        ***                 ***                          ***               ***                            ***             ***                              ***           ***                                 **         **                                     *       *                                         *****                                            ***                                             ***                                            *****                                        ****   ****                                    ***       ***                                 *****       *****                             *****           *****                         *******           *******                      *******             *******                   ********               ********                ********                 ********             ***********               ***********        ",3);
	m_LargeBomb.addFrame("                                                     **   **                   **   **                 *  *                     *  *                    * *                     * *                      * *                   * *                        * *                 * *                          * *               * *                            * *             * *                              * *           * *                                 *           *                                     *       *                                         *   *                                            * *                                             * *                                            *   *                                        *  *   *  *                                    * *       * *                                 *   *       *   *                             *    *         *    *                         *     *           *     *                      *     *             *      *                  *       *              *       *               *        *              *        *            *          *              *         *        ",3);

	m_staticBox.createStatic(m_world, glm::vec2(5.f, 7.f), GameObject::invView(24, 2), 24 * 2, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	m_dynamicBox.createDynamic(m_world, glm::vec2(5.f, 1.f), GameObject::invView(2, 2), 2 * 2, "0000");

	m_terrain = new Terrain();
}




void GameLayer::onUpdate(float timestep)
{
	//Update everything
	m_world->Step(timestep, 7, 5);

	m_dynamicBox.onUpdate(timestep);

	m_animation.onUpdate(timestep);
	m_SmallBomb.onUpdate(timestep);
	m_LargeBomb.onUpdate(timestep);


	// Render everything
	m_renderer.beginScene(m_camera);

	m_renderer.submit(m_terrain->getMaterial());
	m_renderer.submit(m_staticBox.getMaterial());
	m_renderer.submit(m_dynamicBox.getMaterial());

	for (auto label : m_labels)
	{
		m_renderer.submit(label.getMaterial());
	}

	m_renderer.submit(m_animation.getMaterial());
	m_renderer.submit(m_SmallBomb.getMaterial());
	m_renderer.submit(m_LargeBomb.getMaterial());
	m_renderer.submit(m_sBombUI.getMaterial());
	m_renderer.submit(m_lBombUI.getMaterial());
	//m_renderer.submit(m_rocketUI.getMaterial());

	m_renderer.endScene();
	m_renderer.flush();
}

bool GameLayer::onKeyPress(unsigned int keyCode)
{
	return false;
}
