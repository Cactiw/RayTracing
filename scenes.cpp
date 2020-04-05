//
// Created by cactiw on 05.04.2020.
//

void create_scene(std::vector<Object*> &objects, std::vector<Light*> &lights, Picture &backgroundImage,
        const int &scene) {
    switch (scene) {
        case 1:
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., PICTURE_WIDTH - 1000),
                    GLASS, 100));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. - 600, 250, PICTURE_WIDTH + 700),
                    MIRROR, 250));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. + 600, 250, PICTURE_WIDTH + 700),
                    MIRROR, 250));

            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. - 300, 700, PICTURE_WIDTH + 350),
                    RED_FULL, 250));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. + 300, 700, PICTURE_WIDTH + 350),
                    YELLOW_FULL, 250));

//            objects.push_back(new Figure("resources/cube.obj",
//                                         Vec3f(PICTURE_WIDTH / 2. - 700, PICTURE_HEIGHT - 250.,
//                                                 PICTURE_WIDTH - 100),
//                                         200,
//                                         BLUE_FULL));

//            objects.push_back(new Figure("resources/duck.obj",
//                                         Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT - 500., PICTURE_WIDTH),
//                                         -50,
//                                         BLUE_FULL));

            objects.push_back(new Surface(
                    Vec3f(1, PICTURE_HEIGHT, 0), Vec3f(3, PICTURE_HEIGHT, 0),
                    Vec3f(2, PICTURE_HEIGHT, 1), ORANGE_FULL, WHITE_COLOR
            ));

            backgroundImage = Picture("resources/background.jpg");

            lights.push_back(new Light(Vec3f(PICTURE_WIDTH/ 2., 0, 0), 1));
//            lights.push_back(new Light(Vec3f(PICTURE_WIDTH/ 2., 0, PICTURE_WIDTH + 4000),
//                        1));

            break;
        case 2:

            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., PICTURE_WIDTH),
                    MIRROR, 200));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. + 300, 230, PICTURE_WIDTH * 2 - 1350),
                    GLASS, 150));

            objects.push_back(new Figure("resources/duck.obj",
                                         Vec3f(PICTURE_WIDTH / 2. + 150, PICTURE_HEIGHT - 500., PICTURE_WIDTH - 1000),
                                         -50,
                                         GLASS));

            objects.push_back(new Figure("resources/cube.obj",
                                         Vec3f(PICTURE_WIDTH - 650, 700., PICTURE_WIDTH - 1000),
                                         -200,
                                         GLASS));



            objects.push_back(new Surface(
                    Vec3f(1, 0, 0), Vec3f(3, 0, 0),
                    Vec3f(2, 0, 1), WhITE_FULL
            ));
            objects.push_back(new Surface(
                    Vec3f(1, PICTURE_HEIGHT, 0), Vec3f(3, PICTURE_HEIGHT, 0),
                    Vec3f(2, PICTURE_HEIGHT, 1), WhITE_FULL
            ));
            objects.push_back(new Surface(
                    Vec3f(0, 0, 0), Vec3f(0, 1, 0),
                    Vec3f(0, 0, 1), GREEN_FULL
            ));
            objects.push_back(new Surface(
                    Vec3f(0, 0, 5000), Vec3f(0, 1, 5000),
                    Vec3f(1, 0, 5000), YELLOW_FULL
            ));
            objects.push_back(new Surface(
                    Vec3f(PICTURE_WIDTH, 0, 0), Vec3f(PICTURE_WIDTH, 1, 0),
                    Vec3f(PICTURE_WIDTH, 0, 1), RED_FULL
            ));
            objects.push_back(new Surface(
                    Vec3f(0, 0, -1), Vec3f(0, 1, -1),
                    Vec3f(1, 0, -1), YELLOW_FULL
            ));

            lights.push_back(new Light(Vec3f(PICTURE_WIDTH / 2., 100, PICTURE_WIDTH + 3000),1.6));
            break;
        case 3:
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. - 700, 250, PICTURE_WIDTH + 700),
                    MIRROR, 250));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. + 600, 250, PICTURE_WIDTH + 700),
                    MIRROR, 250));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH / 2., PICTURE_HEIGHT / 2., PICTURE_WIDTH - 1000),
                    GLASS, 150));


            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. - 850, 500, PICTURE_WIDTH + 500),
                    GREEN_FULL, 150));
            objects.push_back(new Sphere(
                    Vec3f(PICTURE_WIDTH/ 2. + 650, 500, PICTURE_WIDTH + 500),
                    BLUE_FULL, 150));

            objects.push_back(new Figure("resources/cat.obj",
                                         Vec3f(PICTURE_WIDTH / 2. - 650, PICTURE_HEIGHT - 50., PICTURE_WIDTH + 200),
                                         -100,
                                         GLASS));

            objects.push_back(new Figure("resources/duck.obj",
                                         Vec3f(PICTURE_WIDTH / 2. + 550, PICTURE_HEIGHT - 250., PICTURE_WIDTH - 600),
                                         -50,
                                         ORANGE_FULL));

            objects.push_back(new Surface(
                    Vec3f(1, PICTURE_HEIGHT, 0), Vec3f(3, PICTURE_HEIGHT, 0),
                    Vec3f(2, PICTURE_HEIGHT, 1), YELLOW_FULL
            ));

            lights.push_back(new Light(Vec3f(PICTURE_WIDTH/ 2., 0, 0), 1));

            backgroundImage = Picture("resources/background.jpg");

            break;
    }

}
