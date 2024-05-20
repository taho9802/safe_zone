Feature: Zone Manager
    As a user
    I want to manage zones in an image
    So that I can detect and manipulate zones in my interest

    Scenario: Add a zone with varying amount of vertices
        Given a zone manager
        

        When I add a zone with vertices (0, 0), (0, 10), (10, 10)
        Then the zone should be added successfully

        When I add a zone with vertices (0, 0), (0, 10), (10, 0), (10, 10)
        Then the zone should be added successfully

        When I add a zone with vertices (0, 0), (0, 10)
        Then the zone should NOT be added successfully

        When I add a zone with vertices (0, 0)
        Then the zone should NOT be added successfully
    
    Scenario: add a zone with overlapping amount of vertices
        Given a zone manager


        When I add a zone with vertices (0, 0), (0, 10) (10, 10), (10, 10)
        Then the zone should be added successfully

        When I add a zone with vertices (0, 0), (0, 10), (0, 10)
        Then the zone should NOT be added successfully

    Scenario: add a zone with extreme vertices (specifically out of window size)
        Given a zone manager
        And the view range is (1000, 1000)


        When I add a zone with vertices (0, 1000), (1001, 0), (1000, 1000)
        Then the zone should not be added successfully

        When I add a zone with vertices (0,1000), (1000, 0), (1000, 1000)
        Then the zone should be added successfully

    Scenario: remove zone
        Given a zone manager and a single Point

        When I give a point (0, 5) along with zone with vertices (0, 10), (10, 10), (10, 0)
        Then the zone should be removed

        When I give a point (0, 10) along with zone with vertices (0, 10), (10, 10), (10, 0)
        Then the zone should be removed

        When I give a point (0, 11) along with a zone with vertices (0, 10), (10, 10), (10, 0)
        Then the zone should NOT be removed