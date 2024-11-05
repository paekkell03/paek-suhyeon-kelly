library(dplyr)
library(tidyr)
library(stringr)

#Loading and Cleaning data
cancerdata <- read.csv("C:/Users/deban/OneDrive/Documents/cancer1.csv")

# Viewing all categories for cleaning
#racecategories <- unique(cancerdata$Race.ethnicity) 
#print(racecategories)
#allagecat <- unique(cancerdata$Age_recode)
#print(allagecat) 
#alltype <- unique(cancerdata$Primary.Site...labeled)
#print(alltype)

# Renaming columns and cleaning dataset for readability
# Grouping certain races, ages brackets and cancer sites together
new_cancerdata <- cancerdata %>%
  rename(Age = Age.recode.with..1.year.olds) %>%
  separate(col = Primary.Site...labeled, 
           into = c("Site", "SpecificSite"),
           sep = "[-]") %>% 
  select(-c("Year.of.diagnosis", "SEER.cause.specific.death.classification")) %>% 
  mutate(
    # Recategorize Race/Ethnicity
    Race.ethnicity = case_when(
      Race.ethnicity %in% c("Chinese", "Filipino", "Korean (1988+)", "Other Asian (1991+)",
                            "Asian Indian (2010+)", "Japanese", "Laotian (1988+)", 
                            "Pakistani (2010+)", "Thai (1994+)", "Asian Indian or Pakistani, NOS (1988+)", 
                            "Hmong (1988+)", "Vietnamese (1988+)", "Kampuchean (1988+)") ~ "All Asian",
      Race.ethnicity %in% c("Hawaiian", "Samoan (1991+)", "Pacific Islander, NOS (1991+)",
                            "Chamorran (1991+)", "Tahitian (1991+)", "Melanesian, NOS (1991+)", 
                            "Tongan (1991+)", "Fiji Islander (1991+)", "Guamanian, NOS (1991+)", 
                            "Micronesian, NOS (1991+)", "Polynesian, NOS (1991+)", 
                            "New Guinean (1991+)") ~ "All Pacific Islander",
      Race.ethnicity %in% c("Other", "Unknown") ~ "Other or Unknown",
      TRUE ~ Race.ethnicity
    ),
    # Recategorize age groups
    Age = case_when(
      Age %in% c("00 years", "01-04 years", "05-09 years") ~ "0-9 years",
      Age %in% c("10-14 years", "15-19 years") ~ "10-19 years",
      Age %in% c("20-24 years", "25-29 years") ~ "20-29 years",
      Age %in% c("30-34 years", "35-39 years") ~ "30-39 years",
      Age %in% c("40-44 years", "45-49 years") ~ "40-49 years",
      Age %in% c("50-54 years", "55-59 years") ~ "50-59 years",
      Age %in% c("60-64 years", "65-69 years") ~ "60-69 years",
      Age %in% c("70-74 years", "75-79 years") ~ "70-79 years",
      Age %in% c("80-84 years", "85+ years") ~ "80+ years",
      TRUE ~ Age
    ),
    # Recategorize by major organ system
    Site = case_when(
      Site %in% c("C18.0", "C18.1", "C18.2", "C18.3", "C18.4", "C18.5", "C18.6",
                  "C18.7", "C18.8", "C18.9", "C19.9", "C20.9", "C21.0", "C21.1", 
                  "C23.9", "C24.0", "C24.1", "C25.0", "C25.1", "C25.2", "C25.8") 
      ~ "Digestive System",
      Site %in% c("C34.0", "C34.1", "C34.2", "C34.3", "C34.8", "C34.9") 
      ~ "Respiratory System",
      Site %in% c("C43.0", "C43.1", "C43.2", "C43.3", "C43.4", "C43.5", "C43.6",
                  "C43.7", "C43.8", "C43.9") 
      ~ "Skin and Related Tissues",
      Site %in% c("C64.9", "C65.9", "C67.0", "C67.1", "C67.2", "C67.3", "C67.4",
                  "C67.5", "C67.6", "C67.7", "C67.8", "C67.9") 
      ~ "Urinary System",
      Site %in% c("C50.0", "C50.1", "C50.2", "C50.3", "C50.4", "C50.5", "C50.6",
                  "C50.8", "C50.9", "C61.9") 
      ~ "Reproductive System",
      Site %in% c("C73.9") 
      ~ "Endocrine System",
      Site %in% c("C81.9", "C82.9", "C83.9", "C85.9", "C88.9", "C90.0", "C91.0") 
      ~ "Lymphatic and Hematopoietic System",
      Site %in% c("C71.0", "C71.1", "C71.2", "C71.3", "C71.4", "C71.5", "C71.6",
                  "C71.7", "C71.8", "C71.9") 
      ~ "Nervous System",
      TRUE ~ "Other"
    )
  ) %>%
  select(Age, Sex, Race.ethnicity, Site, SpecificSite, Survival.months)

#need numeric values to find mean values in the app
new_cancerdata$Survival.months = as.numeric(new_cancerdata$Survival.months)

write.csv(new_cancerdata, "C:/Users/deban/OneDrive/Desktop/Docs/STA R Stuff/cleaned_cancer_data.csv")
#we have created cleaned_cancer_data - a cleaned file ready for use!
