#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Util/Shader.h"
#include "Util/RunTimeEditor.h"
#include "Util/Program.h"
#include "Controls/Camera.h"
#include "ObjectMgr/ObjectMgr.h"
#include "Controls/Keyboard.h"
#include "Controls/Player.h"
#include "Util/Physics.h"
#include "Map/Map.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Program& program, Map& map, RunTimeEditor& editor);

// settings
const unsigned int SCR_WIDTH = 1800;
const unsigned int SCR_HEIGHT = 900;

Player player;
ObjectMgr objMgr;
Physics physics;

// camera
Camera camera(glm::vec3(0.0f, player.PLAYER_EYE_HEIGHT, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Keyboard keyboard;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{

    Program program;
    Map gameMap;
    RunTimeEditor editor;

    program.InitializeGLFW();
    program.ConfigureGLFW();

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SHVIZIL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    program.LoadGLFunctionPointers();

    Shader floorShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");
    Shader marbleWallDirOneShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");
    Shader marbleWallDirTwoShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");
    Shader StoneWallDirOneShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");
    Shader StoneWallDirTwoShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");
    Shader cubeShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");
    Shader ghostGlockShader("Util/3.3.shader.vs", "Util/3.3.shader.fs");

    gameMap.InitializePositions();
    const std::vector<glm::vec3>& cubePositions = gameMap.GetCubePositions();
    const std::vector<glm::vec3>& marbleWallPositions = gameMap.GetMarbleWallPositions();
    const std::vector<glm::vec3>& marbleWallDirTwoPositions = gameMap.GetMarbleWallDirTwoPositions();
    const std::vector<glm::vec3>& floorPositions = gameMap.GetFloorPositions();
    const std::vector<glm::vec3>& stoneWallPositions = gameMap.GetStoneWallPositions();
    const std::vector<glm::vec3>& stoneWallDirTwoPositions = gameMap.GetStoneWallDirTwoPositions();
    const glm::vec3 WeaponSquarePosition = player.getWeaponSquarePosition();

    unsigned int floorVBO, floorVAO;
    objMgr.InitializeFloor(floorVBO, floorVAO);

    unsigned int cubeVBO, cubeVAO;
    objMgr.InitializeCube(cubeVBO, cubeVAO);

    unsigned int marbleWallDirOneVBO, marbleWallDirOneVAO;
    objMgr.InitializeWallDirOne(marbleWallDirOneVBO, marbleWallDirOneVAO);

    unsigned int marbleWallDirTwoVBO, marbleWallDirTwoVAO;
    objMgr.InitializeWallDirTwo(marbleWallDirTwoVBO, marbleWallDirTwoVAO);

    unsigned int stoneWallDirOneVBO, stoneWallDirOneVAO;
    objMgr.InitializeWallDirOne(stoneWallDirOneVBO, stoneWallDirOneVAO);

    unsigned int stoneWallDirTwoVBO, stoneWallDirTwoVAO;
    objMgr.InitializeWallDirTwo(stoneWallDirTwoVBO, stoneWallDirTwoVAO);

    unsigned int weaponSquareVAO, weaponSquareVBO;
    objMgr.InitializeWeaponSquare(weaponSquareVAO, weaponSquareVBO);


    unsigned int floorTexture1, floorTexture2;
    unsigned int cubeTexture1, cubeTexture2;
    unsigned int marbleWallDirOneTexture1, marbleWallDirOneTexture2, marbleWallDirTwoTexture1, marbleWallDirTwoTexture2;
    unsigned int stoneWallDirOneTexture1, stoneWallDirOneTexture2, stoneWallDirTwoTexture1, stoneWallDirTwoTexture2;
    unsigned int GHOST_GLOCK_TEXTURE1, GHOST_GLOCK_TEXTURE2;
    int width, height, nrChannels;

    objMgr.HandleTexture(floorTexture1, floorTexture2, width, height, nrChannels, "Images/goldMarbleTex.jpg");
    objMgr.HandleTexture(cubeTexture1, cubeTexture2, width, height, nrChannels, "Images/container.jpg");
    objMgr.HandleTexture(marbleWallDirOneTexture1, marbleWallDirOneTexture2, width, height, nrChannels, "Images/greyMarbleTex.jpg");
    objMgr.HandleTexture(marbleWallDirTwoTexture1, marbleWallDirTwoTexture2, width, height, nrChannels, "Images/greyMarbleTex.jpg");
    objMgr.HandleTexture(stoneWallDirOneTexture1, stoneWallDirOneTexture2, width, height, nrChannels, "Images/stoneWall.jpg");
    objMgr.HandleTexture(stoneWallDirTwoTexture1, stoneWallDirTwoTexture2, width, height, nrChannels, "Images/stoneWall.jpg");
    objMgr.HandleTexture(GHOST_GLOCK_TEXTURE1, GHOST_GLOCK_TEXTURE2, width, height, nrChannels, "Images/GHOST_GLOCK/0002.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    floorShader.use();
    floorShader.setInt("floorTexture1", 0);

    cubeShader.use();
    cubeShader.setInt("cubeTexture1", 0);

    marbleWallDirOneShader.use();
    marbleWallDirOneShader.setInt("MarbleWallDirOne", 0);

    marbleWallDirTwoShader.use();
    marbleWallDirTwoShader.setInt("MarbleWallDirTwo", 0);

    StoneWallDirOneShader.use();
    StoneWallDirOneShader.setInt("StoneWallDirOne", 0);

    StoneWallDirTwoShader.use();
    StoneWallDirTwoShader.setInt("StoneWallDirTwo", 0);

    ghostGlockShader.use();
    ghostGlockShader.setInt("ghostGlockShader", 0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window, program, gameMap, editor);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floorTexture1);

        program.activateAllShaders(floorShader, cubeShader, marbleWallDirOneShader, marbleWallDirTwoShader, StoneWallDirOneShader, StoneWallDirTwoShader, ghostGlockShader);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
        program.setProjectionOnAllObjects(floorShader, cubeShader, marbleWallDirOneShader, marbleWallDirTwoShader, StoneWallDirOneShader, StoneWallDirTwoShader, ghostGlockShader, projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        program.setViewOnAllObjects(floorShader, cubeShader, marbleWallDirOneShader, marbleWallDirTwoShader, StoneWallDirOneShader, StoneWallDirTwoShader, ghostGlockShader, view);

        // render boxes
        glBindVertexArray(floorVAO);
        for (unsigned int i = 0; i < floorPositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, floorPositions[i]);
            floorShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture1);

        // Bind the Cube VAO before drawing
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < cubePositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            cubeShader.setMat4("model", model);

            if (physics.CheckCollisionOnCamera(camera.Position, cubePositions[i], player.PLAYER_EYE_HEIGHT, objMgr.getCubeLength()))
            {
                // std::cout << "CUBE::CAMERA::COLLISION::DETECTED" << std::endl;
                player.Collision_Cube = true;
            }
            else {
                player.lastSafePosition = camera.Position;
            }

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, marbleWallDirOneTexture1);

        glBindVertexArray(marbleWallDirOneVAO);
        for (unsigned int i = 0; i < marbleWallPositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, marbleWallPositions[i]);
            marbleWallDirOneShader.setMat4("model", model);

            if (physics.CheckCollisionOnCamera(camera.Position, marbleWallPositions[i], player.PLAYER_EYE_HEIGHT, objMgr.getWallLength()))
            {
                // std::cout << "MARBLE::WALL::CAMERA::COLLISION::DETECTED" << std::endl;
                player.Collision_MarbleWall = true;
            }
            else {
                player.lastSafePosition = camera.Position;
            }

            glDrawArrays(GL_TRIANGLES, 0, 6);
            
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, marbleWallDirOneTexture1);

        glBindVertexArray(marbleWallDirTwoVAO);
        for (unsigned int i = 0; i < marbleWallDirTwoPositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, marbleWallDirTwoPositions[i]);
            marbleWallDirTwoShader.setMat4("model", model);

            if (physics.CheckCollisionOnCamera(camera.Position, marbleWallDirTwoPositions[i], player.PLAYER_EYE_HEIGHT, objMgr.getWallLength()))
            {
               // std::cout << "MARBLE::WALL::CAMERA::COLLISION::DETECTED" << std::endl;
                player.Collision_MarbleWallDirTwo = true;
            }
            else {
                player.lastSafePosition = camera.Position;
            }

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, stoneWallDirOneTexture1);

        glBindVertexArray(stoneWallDirOneVAO);
        for (unsigned int i = 0; i < stoneWallPositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

            if (i >= 55)
            {
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            }

            model = glm::translate(model, stoneWallPositions[i]);
            StoneWallDirOneShader.setMat4("model", model);

            if (physics.CheckCollisionOnCamera(camera.Position, stoneWallPositions[i], player.PLAYER_EYE_HEIGHT, objMgr.getWallLength()))
            {
                //std::cout << "STONE::WALL::CAMERA::COLLISION::DETECTED" << std::endl;
                player.Collion_StoneWall = true;
            }
            else {
                player.lastSafePosition = camera.Position;
            }

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, stoneWallDirOneTexture1);

        glBindVertexArray(stoneWallDirTwoVAO);
        for (unsigned int i = 0; i < stoneWallDirTwoPositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, stoneWallDirTwoPositions[i]);
            StoneWallDirTwoShader.setMat4("model", model);

            if (physics.CheckCollisionOnCamera(camera.Position, stoneWallDirTwoPositions[i], player.PLAYER_EYE_HEIGHT, objMgr.getWallLength()))
            {
                //std::cout << "STONE::WALL::CAMERA::COLLISION::DETECTED" << std::endl;
                player.Collision_StoneWallDirTwo = true;
            }
            else {
                player.lastSafePosition = camera.Position;
            }

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        /*glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, GHOST_GLOCK_TEXTURE1);

        glBindVertexArray(weaponSquareVAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, WeaponSquarePosition);
        ghostGlockShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 6);*/
        // Unbind the VAO after drawing
        //glBindVertexArray(0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteBuffers(1, &floorVBO);
    // glDeleteVertexArrays(1, &cubeVAO);
    // glDeleteBuffers(1, &cubeVAO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, Program& program, Map& map, RunTimeEditor& editor)
{
    player.UpdateState();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);

    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (!player.Collision)
        {
            camera.ProcessKeyboard(FORWARD, deltaTime, editor.NO_CLIP_STATE);
            player.isMoving = true;
        }
        
        if (player.Collision)
        {
            std::vector<glm::vec3> collidedWith = map.PlayerCollidedWith(player);
            program.ValidateMoveAfterCollision(FORWARD, camera, physics, player, collidedWith, deltaTime);
            collidedWith.clear();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (!player.Collision)
        {
            camera.ProcessKeyboard(BACKWARD, deltaTime, editor.NO_CLIP_STATE);
            player.isMoving = true;
        }

        if (player.Collision)
        {
            std::vector<glm::vec3> collidedWith = map.PlayerCollidedWith(player);
            program.ValidateMoveAfterCollision(BACKWARD, camera, physics, player, collidedWith, deltaTime);
            collidedWith.clear();
        }
        
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if (!player.Collision)
        {
            camera.ProcessKeyboard(LEFT, deltaTime, editor.NO_CLIP_STATE);
            player.isMoving = true;
        }
        
        if (player.Collision)
        {
            std::vector<glm::vec3> collidedWith = map.PlayerCollidedWith(player);
            program.ValidateMoveAfterCollision(LEFT, camera, physics, player, collidedWith, deltaTime);
            collidedWith.clear();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if (!player.Collision)
        {
            camera.ProcessKeyboard(RIGHT, deltaTime, editor.NO_CLIP_STATE);
            player.isMoving = true;
        }
        
        if (player.Collision)
        {
            std::vector<glm::vec3> collidedWith = map.PlayerCollidedWith(player);
            program.ValidateMoveAfterCollision(RIGHT, camera, physics, player, collidedWith, deltaTime);
            collidedWith.clear();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        keyboard.Crouch(camera.Position, player.PLAYER_EYE_HEIGHT, player.isCrouched);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        player.isShiftWalking = false;
        camera.MovementSpeed = SPEED;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
    {
        camera.Position.y = player.PLAYER_EYE_HEIGHT;
        player.isCrouched = false;
        camera.MovementSpeed = SPEED;
    }

    if (player.isCrouched)
        keyboard.CrouchWalk(camera.MovementSpeed);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        keyboard.ShiftWalk(camera.MovementSpeed, player.isShiftWalking);
    
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        editor.drawWireFrames();

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        editor.drawFilled();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        player.isMoving = false;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        player.isMoving = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        player.isMoving = false;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        player.isMoving = false;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}